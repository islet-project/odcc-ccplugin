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

import java.io.File;

import android.content.res.AssetManager;
import android.os.Looper;
import android.annotation.Nullable;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * A simplified version of Context for use in minimal Android runtime environments.
 *
 * <p>This abstract class provides access to application-specific resources and classes,
 * as well as up-calls for application-level operations such as launching activities,
 * broadcasting and receiving intents, etc.</p>
 */
public abstract class Context {
    /**
     * Create a new context instance.
     */
    public Context() {
    }

    /**
     * Returns the absolute path to the directory on the filesystem where files
     * created with {@link #openFileOutput} are stored.
     *
     * <p>This is a simplified implementation that returns a fixed path.</p>
     *
     * @return The path to the files directory.
     */
    public File getFilesDir() {
        return new File("/data/local/tmp");
    }

    /**
     * Return the context of the single, global Application object of the
     * current process.
     *
     * @return The application context.
     */
    public abstract Context getApplicationContext();

    /**
     * Return the Looper for the main thread of the current process.
     *
     * @return The main looper.
     */
    public abstract Looper getMainLooper();

    /**
     * Return an AssetManager instance for the application's package.
     *
     * @return An AssetManager instance.
     */
    public abstract AssetManager getAssets();

    /** Shared preferences mode: Access is limited to the application itself. */
    public static int MODE_PRIVATE = 0;
    /** Shared preferences mode: Allow all other applications to have read access. */
    public static int MODE_WORLD_READABLE = 1;
    /** Shared preferences mode: Allow all other applications to have write access. */
    public static int MODE_WORLD_WRITEABLE = 2;
    /** Database open flag: Enable write-ahead logging. */
    public static int MODE_ENABLE_WRITE_AHEAD_LOGGING = 3;
    /** Database open flag: Don't localize collators. */
    public static int MODE_NO_LOCALIZED_COLLATORS = 4;

    /** Activity service name. */
    public static final String ACTIVITY_SERVICE = "activity";
}
