/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=java -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja -o external/CCPlugIn/gen -N . -N vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IExampleInterface.aidl
 */
package com.examplecc.service;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;

import com.islet.binder.service.Reader;
import com.islet.binder.service.Logger;
import com.islet.binder.service.VmManager;
import com.islet.binder.service.IRealmService;
import com.examplecc.service.IExampleInterface;

public class ExampleService extends Service implements VmManager.VmServiceCallback {
  private static final String TAG = "ExampleService";
  private Logger mLogger;
  private VmManager mVmManager;
  private IExampleInterface mTargetService = null;

  private final IExampleInterface.Stub mBinder = new IExampleInterface.Stub() {
    @Override
    public void doSomething() throws RemoteException {
      mLogger.write(String.format("Entering %s()", "mBinder.doSomething"));
      if (mTargetService != null) {
        mTargetService.doSomething();
      } else {
        mLogger.write("Target service is not available yet");
        throw new RemoteException("Target service is not available");
      }
      mLogger.write("mBinder.doSomething()");
    }

    @Override
    public int addInt(int a, int b) throws RemoteException {
      mLogger.write(String.format("Entering %s(%d, %d)", "mBinder.addInt", a, b));
      int ret;
      if (mTargetService != null) {
        ret = mTargetService.addInt(a, b);
        mLogger.write("addInt() returning: " + ret);
        return ret;
      } else {
        mLogger.write("Target service is not available yet");
        throw new RemoteException("Target service is not available");
      }
    }

    @Override
    public int getRandomNumber() throws RemoteException {
      mLogger.write(String.format("Entering %s()", "mBinder.getRandomNumber"));
      int ret;
      if (mTargetService != null) {
        ret = mTargetService.getRandomNumber();
        mLogger.write("getRandomNumber() returning: " + ret);
        return ret;
      } else {
        mLogger.write("Target service is not available yet");
        throw new RemoteException("Target service is not available");
      }
    }

    @Override
    public void getRandomNumberFromCallback(com.examplecc.service.IResponse response) throws RemoteException {
      mLogger.write(String.format("Entering %s(%s)", "mBinder.getRandomNumberFromCallback", response));
      com.examplecc.service.IResponse proxy_response = new com.examplecc.service.IResponse.Stub() {
        @Override
        public void onResponse(java.lang.String message, int res) throws RemoteException {
          mLogger.write("onResponse() called from realm world");
          response.onResponse(message, res);
        }

        @Override
        public void onError(java.lang.String message) throws RemoteException {
          mLogger.write("onError() called from realm world");
          response.onError(message);
        }
      };
      if (mTargetService != null) {
        mTargetService.getRandomNumberFromCallback(proxy_response);
      } else {
        mLogger.write("Target service is not available yet");
        throw new RemoteException("Target service is not available");
      }
      mLogger.write("mBinder.getRandomNumberFromCallback()");
    }
  };

  @Override
  public void onCreate() {
    mLogger = new Logger(this, TAG, "service2.txt");
    mVmManager = new VmManager(getApplication(), mLogger);
    mLogger.write("Entering onCreate();");

    // Set VM service callback to receive notifications
    mVmManager.setVmServiceCallback(this);

    mVmManager.vmRun();
    // we cannot call mVmManager.getVMService().onCreate() here as the service is
    // not connected yet

    mLogger.write("Returning onCreate();");
  }

  @Override
  public IBinder onBind(Intent intent) {
    mLogger.write("Entering onBind();");

    // we cannot call mVmManager.getVMService().onBind() here as the service is not
    // connected yet

    mLogger.write("Returning onBind();");
    return mBinder;
  }

  @Override
  public boolean onUnbind(Intent intent) {
    mLogger.write("Entering onUnbind();");
    mLogger.write("Returning onUnbind();");
    return false; // return true if you want onRebind() to be called later
  }

  @Override
  public void onDestroy() {
    mLogger.write("Entering onDestroy();");

    mVmManager.vmStop();

    mLogger.write("Returning onDestroy();");
  }

  // VmServiceCallback implementation
  @Override
  public void onVmServiceReady(IRealmService vmService) {
    mLogger.write("VM service is ready! Connection established successfully.");

    // You can perform additional initialization work here when VM service is ready.
    // For example: call specific VM service methods, set up states, etc.
    try {
      // Call onBindForTargetService to get the target service binder
      IBinder targetBinder = vmService.onBindForTargetService();
      if (targetBinder != null) {
        // Convert binder to IExampleInterface
        mTargetService = IExampleInterface.Stub.asInterface(targetBinder);
        mLogger.write("Target service binder successfully obtained and converted.");
      } else {
        mLogger.write("Failed to obtain target service binder - binder is null.");
      }
    } catch (Exception e) {
      mLogger.write("Error in onVmServiceReady: " + e.getMessage());
    }
  }

  @Override
  public void onVmServiceError(String errorMessage) {
    mLogger.write("VM service error occurred: " + errorMessage);

    // You can implement error handling logic here when VM service connection fails.
    // For example: retry logic, notify user, fallback behavior, etc.
    mLogger.write("Handling VM service connection error...");
  }
}
