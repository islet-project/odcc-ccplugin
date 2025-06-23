/*
 * Copyright (C) 2006 The Android Open Source Project
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Samsung's changes: add support for Islet/Arm CCA CC services

package android.app;

import android.content.ContextWrapper;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

import java.util.List;
import java.util.ArrayList;

import com.android.internal.os.ClassLoaderFactory;

/**
 * A slimmed-down version of Service for use in minimal Android runtime environments.
 *
 * <p>This abstract class is used by VM realms running Android bound CC services to provide
 * background processing capabilities.</p>
 */
public abstract class Service extends ContextWrapper {
    /**
     * The class loader used by this service.
     */
    public ClassLoader mClassLoader;

    /**
     * Create a new service instance.
     */
    public Service() {
        super();
    }

    /**
     * Called by the system when the service is first created.
     *
     * <p>Initializes the class loader with the confidential service dex file.</p>
     */
    public void onCreate() {
        ClassLoader parent = ClassLoader.getSystemClassLoader().getParent();
        List<String> nativeSharedLibraries = new ArrayList<>();
        nativeSharedLibraries.add("ALL");

        mClassLoader = ClassLoaderFactory.createClassLoader(
            "/mnt/apk/assets/confidential-service.dex",
            "/apex/com.android.art/javalib/:/apex/com.android.os.statsd/javalib/:/apex/com.android.i18n/javalib/",
            "",
            parent,
            15,
            true,
            "CCServiceClassLoader",
            null,
            nativeSharedLibraries,
            null);
    }

    /**
     * Called by the system when the service is destroyed.
     *
     * <p>Override this method to perform cleanup operations before the service is destroyed.</p>
     */
    public void onDestroy() {
    }

    /**
     * Return the communication channel to the service.
     *
     * @param intent The Intent that was used to bind to this service
     * @return Return an IBinder through which clients can call on to the service
     */
    public abstract IBinder onBind(Intent intent);

    /**
     * Called when all clients have disconnected from a particular interface published by the service.
     *
     * @param intent The Intent that was used to bind to this service
     * @return Return true if you would like to have the service's onRebind(Intent) method called
     */
    public boolean onUnbind(Intent intent) {
        return false;
    }
}
