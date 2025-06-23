/*
 * Copyright (C) 2006 The Android Open Source Project
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

package android.content.res;

import android.annotation.NonNull;
import android.os.ParcelFileDescriptor;
import android.ravenwood.annotation.RavenwoodKeepWholeClass;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Objects;

/**
 * A slimmed-down version of AssetManager used by minimal Android runtime to run bound services.
 *
 * <p>This class provides access to application assets bundled with the application as resources.
 * Assets are read-only and are stored in the "assets" directory of the application's APK.</p>
 */
@RavenwoodKeepWholeClass
public final class AssetManager implements AutoCloseable {
    /**
     * Close this asset manager.
     */
    @Override
    public void close() {
    }

    /**
     * Open an uncompressed asset by mmapping it and returning an {@link AssetFileDescriptor}.
     * This provides access to files that have been bundled with an application as assets -- that
     * is, files placed in to the "assets" directory.
     *
     * The asset must be uncompressed, or an exception will be thrown.
     *
     * @param fileName The name of the asset to open.  This name can be hierarchical.
     * @return An open AssetFileDescriptor.
     */
    public @NonNull AssetFileDescriptor openFd(@NonNull String fileName) throws IOException {
        Objects.requireNonNull(fileName, "fileName");
        synchronized (this) {
            // ensureOpenLocked();
            //final ParcelFileDescriptor pfd = nativeOpenAssetFd(mObject, fileName, mOffsets);
            final ParcelFileDescriptor pfd = openAssetFd(fileName);
            if (pfd == null) {
                throw new FileNotFoundException("Asset file: " + fileName);
            }
            return new AssetFileDescriptor(pfd, 0, AssetFileDescriptor.UNKNOWN_LENGTH);
        }
    }

    /**
     * The path to the assets folder where application assets are stored.
     */
    private final String ASSETS_FOLDER = "/mnt/apk/assets/";

    /**
     * Opens an asset file descriptor for the specified file name.
     *
     * @param fileName The name of the asset file to open
     * @return A ParcelFileDescriptor for the asset file, or null if the file is not found
     */
    private ParcelFileDescriptor openAssetFd(String fileName) {
        File file = new File(ASSETS_FOLDER + fileName);
        try {
            return ParcelFileDescriptor.open(file, ParcelFileDescriptor.MODE_READ_ONLY);
        } catch(FileNotFoundException ex) {
            return null;
        }
    }

}
