// Copyright (C) 2021 The Android Open Source Project
// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package com.islet.binder.service;

import android.content.Context;
import android.util.Log;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;

/**
 * Reader class that implements Runnable to read data from an input stream
 * and post it to a logger.
 *
 * <p>This class is designed to be used in a separate thread to continuously
 * read from an input stream (such as process output) and write the data
 * to a logger for further processing or storage.</p>
 */
public class Reader implements Runnable {
    /** Tag used for logging errors within this reader instance. */
    private final String mTag;

    /** Name identifier for this reader instance. */
    private final String mName;

    /** Input stream from which data is read. */
    private final InputStream mStream;

    /** Logger instance used to write the read data. */
    private final Logger mLogger;

    /**
     * Constructs a new Reader instance.
     *
     * @param context The Android context used for logger initialization
     * @param tag The tag used for logging errors
     * @param name The name identifier for this reader instance
     * @param stream The input stream from which data will be read
     */
    public Reader(Context context, String tag, String name, InputStream stream) {
        mTag = tag;
        mName = name;
        mStream = stream;
        mLogger = new Logger(context, tag, mName);
    }

    /**
     * Runs the reader loop, continuously reading from the input stream
     * and writing each line to the logger.
     *
     * <p>This method will continue reading until either:
     * <ul>
     * <li>The end of the stream is reached (readLine() returns null)</li>
     * <li>The thread is interrupted</li>
     * <li>An IOException occurs</li>
     * </ul>
     * </p>
     *
     * <p>Any IOExceptions that occur during reading are caught and logged
     * using the Android Log utility with the error level.</p>
     */
    @Override
    public void run() {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(mStream));
            String line;
            while ((line = reader.readLine()) != null && !Thread.interrupted()) {
                mLogger.write(line);
            }
        } catch (IOException e) {
            Log.e(mTag, "Exception while posting " + mName + " output: " + e.getMessage());
        }
    }
}
