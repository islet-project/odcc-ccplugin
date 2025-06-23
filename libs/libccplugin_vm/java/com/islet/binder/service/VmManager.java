// Copyright (C) 2021 The Android Open Source Project
// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package com.islet.binder.service;

import android.content.Context;
import android.os.IBinder;
import android.os.RemoteException;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.io.InputStream;

import android.system.virtualmachine.VirtualMachine;
import android.system.virtualmachine.VirtualMachineCallback;
import android.system.virtualmachine.VirtualMachineConfig;
import android.system.virtualmachine.VirtualMachineException;
import android.system.virtualmachine.VirtualMachineManager;

import com.islet.binder.service.IRealmService;
import com.islet.binder.service.Reader;
import com.islet.binder.service.Logger;

/**
 * Host-side lifecycle for the Realm (aka, confidential virtual machine): builds config from
 * {@code assets/vm_configs/vm_config.json}, starts the VM, and when the payload is ready connects
 * to IRealmService over vsock (same port as {@code IRealmService.PORT} in the AIDL). When debug is enabled, VM console
 * and log output are appended to local log files through Reader.
 */
public class VmManager {
    private static final boolean VM_DEBUG = true;
    private static final boolean VM_PROTECTED = false;
    private static final String VM_NAME = "RealmService";
    private static final String TAG = "VmManager";

    private final Context context;
    private final Logger mLogger;

    private VirtualMachine mVirtualMachine;
    private ExecutorService mVMLogThreads;
    private IRealmService mVMService = null;
    private VmServiceCallback mVmServiceCallback = null;

    /** Supplier that may throw RemoteException for use with {@link #vmServiceRun}. */
    @FunctionalInterface
    public interface ThrowingSupplier<T> {
        T run() throws RemoteException;
    }

    /** Listener for asynchronous Realm binder availability after the payload starts. */
    public interface VmServiceCallback {
        /** Called when IRealmService is connected. */
        void onVmServiceReady(IRealmService vmService);

        /** Called if vsock connection or binder setup fails (see log lines for detail). */
        void onVmServiceError(String errorMessage);
    }

    public VmManager(Context context, Logger logger) {
        this.context = context;
        this.mLogger = logger;
    }

    public void setVmServiceCallback(VmServiceCallback callback) {
        this.mVmServiceCallback = callback;
    }

    /**
     * @throws IllegalStateException if the VM is not running or the Realm binder is not connected yet
     */
    public IRealmService getVMService() {
        if (mVirtualMachine == null || mVirtualMachine.getStatus() != VirtualMachine.STATUS_RUNNING) {
            throw new IllegalStateException("VM is not running now");
        }
        if (mVMService == null) {
            throw new IllegalStateException("mVMService is null");
        }

        return mVMService;
    }

    VirtualMachineCallback mVMCallback = new VirtualMachineCallback() {
        @Override
        public void onPayloadStarted(VirtualMachine vm) {
            mLogger.write("Entering mVMCallback.onPayloadStarted();");
        }

        @Override
        public void onPayloadReady(VirtualMachine vm) {
            mLogger.write("Entering mVMCallback.onPayloadReady();");
            mLogger.write("Payload is ready, connecting to VM...");

            try {
                IBinder binder = vm.connectToVsockServer(IRealmService.PORT);
                mVMService = IRealmService.Stub.asInterface(binder);

                // Notify callback that VM service is ready
                if (mVmServiceCallback != null && mVMService != null) {
                    mVmServiceCallback.onVmServiceReady(mVMService);
                }
            } catch (Exception e) {
                if (!Thread.interrupted()) {
                    mVMService = null;
                    mLogger.write("VM service connection failed: " + e.getMessage());

                    // Notify callback about the error
                    if (mVmServiceCallback != null) {
                        mVmServiceCallback.onVmServiceError("VM service connection failed: " + e.getMessage());
                    }
                }
            }
        }

        // Called when payload quits by itself, e.g. mVM.quit() -> exit(0)
        @Override
        public void onPayloadFinished(VirtualMachine vm, int exitCode) {
            mLogger.write("Entering mVMCallback.onPayloadFinished();");

            mLogger.write("Payload finished, exit code: " + exitCode);
        }

        @Override
        public void onError(VirtualMachine vm, int errorCode, String message) {
            mLogger.write("Entering mVMCallback.onError();");

            mLogger.write("Error occurred, code: " + errorCode + ", message: " + message);
        }

        // Seems it's always called when VM stops, regardless of reason
        @Override
        public void onStopped(VirtualMachine vm, int reason) {
            mLogger.write("Entering mVMCallback.onStopped();");

            mVMLogThreads.shutdownNow();
            mVMLogThreads = null;
            mVMService = null;
            mVirtualMachine = null;
        }
    };

    /**
     * Runs {@code task} on the connected IRealmService. Call only after
     * {@link VmServiceCallback#onVmServiceReady}.
     *
     * @throws RemoteException if the VM is not running, not connected, or {@code task} fails
     */
    public <T> T vmServiceRun(ThrowingSupplier<T> task) throws RemoteException {
        if (vmGetStatus() != VirtualMachine.STATUS_RUNNING) {
            mLogger.write("VM is not running");
            throw new RemoteException("VM is not running");
        }
        if (mVMService == null) {
            mLogger.write("VM not connected");
            throw new RemoteException("VM not connected");
        }
        try {
            return task.run();
        } catch (RemoteException e) {
            mLogger.write("Exception during operation: " + e.getMessage());
            throw new RemoteException("Exception during operation: " + e.getMessage());
        }
    }

    public void vmRun() {
        mLogger.write("Entering vmRun();");

        // Create a VM and run it.
        mVMLogThreads = Executors.newFixedThreadPool(2);

        try {
            VirtualMachineConfig.Builder builder = new VirtualMachineConfig.Builder(context);
            builder.setPayloadConfigPath("assets/vm_configs/vm_config.json");
            builder.setProtectedVm(VM_PROTECTED);
            builder.setMemoryBytes(2048L * 1024 * 1024);
            builder.setEncryptedStorageBytes(128L * 1024 * 1024); // 128 MB of encryptedstore

            if (VM_DEBUG) {
                builder.setDebugLevel(VirtualMachineConfig.DEBUG_LEVEL_FULL);
                builder.setVmOutputCaptured(true);
                builder.setConnectVmConsole(true);
            }

            VirtualMachineConfig config = builder.build();
            VirtualMachineManager vmm = context.getSystemService(VirtualMachineManager.class);
            mVirtualMachine = vmm.getOrCreate(VM_NAME, config);
            try {
                mVirtualMachine.setConfig(config);
            } catch (VirtualMachineException e) {
                // getOrCreate may return an instance that rejects this config; drop and recreate.
                vmm.delete(VM_NAME);
                mVirtualMachine = vmm.create(VM_NAME, config);
            }
            mVirtualMachine.run();
            mVirtualMachine.setCallback(Executors.newSingleThreadExecutor(), mVMCallback);

            if (VM_DEBUG) {
                InputStream console = mVirtualMachine.getConsoleOutput();
                InputStream log = mVirtualMachine.getLogOutput();
                mVMLogThreads.execute(new Reader(context, TAG, "console.txt", console));
                mVMLogThreads.execute(new Reader(context, TAG, "realm.txt", log));
            }
        } catch (VirtualMachineException e) {
            mVMLogThreads.shutdownNow();
            mVMLogThreads = null;
            mVirtualMachine = null;
            throw new RuntimeException(e);
        }
    }

    public void vmStop() {
        mLogger.write("Entering vmStop();");

        if (vmGetStatus() != VirtualMachine.STATUS_RUNNING) {
            mLogger.write("VM already stopped");
            return;
        }

        mLogger.write("Attempting to stop VM");
        try {
            mVirtualMachine.stop();
        } catch (VirtualMachineException e) {
            mLogger.write("Stopping VM failed: " + e.getMessage());
        }
    }

    public Integer vmGetStatus() {
        if (mVirtualMachine == null) {
            // No live handle (never started or cleared in onStopped).
            return VirtualMachine.STATUS_DELETED;
        }
        return mVirtualMachine.getStatus();
    }

}
