// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package com.islet.binder.service;

import android.content.Context;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * Logger class for writing log messages to a file.
 * This class provides functionality to create a log file and write messages to it.
 * It also handles errors by logging them to the Android log system.
 */
public class Logger {
    private final String mTag;
    private final String mFileName;
    private final File mLogFile;

    /**
     * Constructs a new Logger instance.
     *
     * @param context The Android context used to access the application's file directory
     * @param tag The tag used for Android log messages
     * @param fileName The name of the log file to create
     */
    public Logger(Context context, String tag, String fileName) {
        mTag = tag;
        mFileName = fileName;
        mLogFile = new File(context.getFilesDir(), mFileName);

        try (FileOutputStream fos = new FileOutputStream(mLogFile, true)) {
            // Opening with 'false' truncates the file
            // Opening with 'true' appends the file
        } catch (IOException e) {
            Log.e(mTag, "Cannot create log file " + mFileName + ": " + e.getMessage());
            e.printStackTrace();
        }
    }

    /**
     * Writes a message to the log file.
     *
     * @param message The message to write to the log file
     */
    public void write(String message) {
        try (FileOutputStream fos = new FileOutputStream(mLogFile, true)) {
            fos.write((message + "\n").getBytes());
        } catch (IOException e) {
            Log.e(mTag, "Cannot write log file " + mFileName + ": " + e.getMessage());
        }
    }
}
