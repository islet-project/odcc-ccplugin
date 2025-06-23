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

package android.content;

import android.content.Context;
import android.content.res.AssetManager;
import android.os.Looper;
import android.os.FileUtils;
import android.util.Log;

import java.io.File;

/**
 * A simplified version of ContextWrapper for use in minimal Android runtime environments.
 *
 * <p>This class provides a wrapper around a Context object, delegating calls to the wrapped context.</p>
 */
public class ContextWrapper extends Context {
    /**
     * Create a new context wrapper instance.
     */
    public ContextWrapper() {
    }

    /**
     * Return the context of the single, global Application object of the
     * current process.
     *
     * <p>This implementation returns a singleton instance of ContextWrapper.</p>
     *
     * @return The application context.
     */
    @Override
    public Context getApplicationContext() {
        Context result = sInstance;
        if (result != null) {
            return result;
        }

        synchronized(ContextWrapper.class) {
            if (sInstance == null) {
                sInstance = new ContextWrapper();
            }
            return sInstance;
        }
    }

    /**
     * Return the Looper for the main thread of the current process.
     *
     * @return The main looper.
     */
    @Override
    public Looper getMainLooper() {
        return Looper.getMainLooper();
    }

    /**
     * Set file permissions based on the mode.
     *
     * @param name The name of the file.
     * @param mode The mode to set.
     * @param extraPermissions Additional permissions to set.
     */
    static void setFilePermissionsFromMode(String name, int mode,
            int extraPermissions) {
        int perms = FileUtils.S_IRUSR|FileUtils.S_IWUSR
            |FileUtils.S_IRGRP|FileUtils.S_IWGRP
            |extraPermissions;
        if ((mode&MODE_WORLD_READABLE) != 0) {
            perms |= FileUtils.S_IROTH;
        }
        if ((mode&MODE_WORLD_WRITEABLE) != 0) {
            perms |= FileUtils.S_IWOTH;
        }

        FileUtils.setPermissions(name, perms, -1, -1);
    }

    /**
     * Return an AssetManager instance for the application's package.
     *
     * @return An AssetManager instance.
     */
    @Override
    public AssetManager getAssets() {
        return new AssetManager();
    }

    /** Singleton instance of ContextWrapper. */
    private static volatile Context sInstance;
}
