/*
 * Copyright (C) 2026 The Android Open Source Project
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

package android.util;


import android.annotation.IntDef;
import android.annotation.NonNull;
import android.annotation.Nullable;
import android.compat.annotation.UnsupportedAppUsage;

import java.io.FileWriter;
import java.io.IOException;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * A simplified version of Log for use in minimal Android runtime environments.
 *
 * <p>This class provides logging functionality for VM realms running Android bound services.
 * It offers methods for logging at different priority levels, although reagardless of used log level
 * all messages are written into the dedicated console log</p>
 */
public class Log {
    /**
     * Log priority levels annotation.
     */
    @IntDef({ASSERT, ERROR, WARN, INFO, DEBUG, VERBOSE})
    @Retention(RetentionPolicy.SOURCE)
    public @interface Level {}

    /**
     * Private method to write log messages to the system.
     *
     * @param tag The tag associated with the log message
     * @param msg The log message
     * @return An integer status code
     */
    private static int write(String tag, String msg) {
        String message = tag + ": " + msg;

        // Afraid this won't work in Microdroid anyway. __android_log_write() in
        // CPP uses logd that is forwarded to the Android logs. Std error is
        // not. There also doesn't seem to be any directory on Microdroid that
        // is writeable by the system_payload user.
        System.err.println(message);

        // This doesn't seem to work anyway even though it should in theory,
        // /dev/console is 0666 and is intercepted by the Android. Works in
        // shell, doesn't work here though. Can't see why yet.
        try (FileWriter fw = new FileWriter("/dev/console", true)) {
            fw.write(message + "\n");
        } catch (IOException e) {}

        return 1;
    }

    /**
     * Send an ERROR log message.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @return An integer status code
     */
    public static int e(String tag, String msg) {
        return write(tag, msg);
    }

    /**
     * Send an ERROR log message and log the exception.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @param tr An exception to log
     * @return An integer status code
     */
    public static int e(String tag, String msg, Throwable tr) {
        return write(tag, msg + tr.toString());
    }

    /**
     * Send a DEBUG log message.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @return An integer status code
     */
    public static int d(String tag, String msg) {
        return write(tag, msg);
    }

    /**
     * Send a DEBUG log message and log the exception.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @param tr An exception to log
     * @return An integer status code
     */
    public static int d(String tag, String msg, Throwable tr) {
        return write(tag, msg + tr.toString());
    }

    /**
     * Send a VERBOSE log message.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @return An integer status code
     */
    public static int v(String tag, String msg) {
        return write(tag, msg);
    }

    /**
     * Send a VERBOSE log message and log the exception.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @param tr An exception to log
     * @return An integer status code
     */
    public static int v(String tag, String msg, Throwable tr) {
        return write(tag, msg + tr.toString());
    }

    /**
     * Send an INFO log message.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @return An integer status code
     */
    public static int i(String tag, String msg) {
        return write(tag, msg);
    }

    /**
     * Send an INFO log message and log the exception.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @param tr An exception to log
     * @return An integer status code
     */
    public static int i(String tag, String msg, Throwable tr) {
        return write(tag, msg + tr.toString());
    }

    /**
     * Send a WARN log message.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @return An integer status code
     */
    public static int w(String tag, String msg) {
        return write(tag, msg);
    }

    /**
     * Send a WARN log message and log the exception.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @param tr An exception to log
     * @return An integer status code
     */
    public static int w(String tag, String msg, Throwable tr) {
        return write(tag, msg + tr.toString());
    }

    /**
     * What a Terrible Failure: Report a condition that should never happen.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @return An integer status code
     */
    public static int wtf(String tag, String msg) {
        return write(tag, msg);
    }

    /**
     * What a Terrible Failure: Report a condition that should never happen.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param tr An exception to log
     * @return An integer status code
     */
    public static int wtf(@Nullable String tag, @NonNull Throwable tr) {
        return wtf(LOG_ID_MAIN, tag, tr.getMessage(), tr, false, false);
    }

    /**
     * What a Terrible Failure: Report a condition that should never happen.
     *
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @param tr An exception to log
     * @return An integer status code
     */
    public static int wtf(@Nullable String tag, @Nullable String msg, @Nullable Throwable tr) {
        return wtf(LOG_ID_MAIN, tag, msg, tr, false, false);
    }

    /**
     * What a Terrible Failure: Report a condition that should never happen.
     *
     * @param logId The log buffer ID
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @param tr An exception to log
     * @param localStack Whether to include the local stack trace
     * @param system Whether this is a system-level log
     * @return An integer status code
     */
    @UnsupportedAppUsage
    static int wtf(int logId, @Nullable String tag, @Nullable String msg, @Nullable Throwable tr,
            boolean localStack, boolean system) {
        return write(tag, msg + tr.toString());
    }

    /**
     * Prints all specified log information to the log.
     *
     * @param bufID The log buffer ID
     * @param priority The priority of the log message
     * @param tag Used to identify the source of a log message. It usually identifies the class or activity where the log call occurs.
     * @param msg The message you would like logged.
     * @param tr An exception to log
     * @return An integer status code
     */
    public static int printlns(int bufID, int priority, @Nullable String tag, @NonNull String msg,
            @Nullable Throwable tr) {
        return write(tag, msg + tr.toString());
    }

    /**
     * Checks to see whether or not a log for the specified tag is loggable at the specified level.
     *
     * @param tag The tag to check
     * @param level The level to check
     * @return true if the log is loggable
     */
    public static boolean isLoggable(String tag, int level) {
        return true;
    }

    /**
     * Handy function to get a loggable stack trace from a Throwable.
     *
     * @param tr An exception to log
     * @return The stack trace string
     */
    @NonNull
    public static String getStackTraceString(@Nullable Throwable tr) {
        return null;
    }

    /** @hide Main log buffer ID */
    public static final int LOG_ID_MAIN = 0;
    /** @hide Radio log buffer ID */
    public static final int LOG_ID_RADIO = 1;
    /** @hide Events log buffer ID */
    public static final int LOG_ID_EVENTS = 2;
    /** @hide System log buffer ID */
    public static final int LOG_ID_SYSTEM = 3;
    /** @hide Crash log buffer ID */
    public static final int LOG_ID_CRASH = 4;

    /** Priority constant for the println method; use Log.v. */
    public static final int VERBOSE = 2;
    /** Priority constant for the println method; use Log.d. */
    public static final int DEBUG = 3;
    /** Priority constant for the println method; use Log.i. */
    public static final int INFO = 4;
    /** Priority constant for the println method; use Log.w. */
    public static final int WARN = 5;
    /** Priority constant for the println method; use Log.e. */
    public static final int ERROR = 6;
    /** Priority constant for the println method. */
    public static final int ASSERT = 7;
}