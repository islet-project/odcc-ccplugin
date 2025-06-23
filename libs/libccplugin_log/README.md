# Log library (libccplugin_log)

## Overview

This library provides logging functionality for the CCPlugIn framework, enabling applications to capture and store log output from the Realm and CC Service. It consists of two main components:

1. **Logger** - A class that writes log messages to a file in the application's private storage
2. **Reader** - A Runnable class that reads data from an input stream (such as process output) and writes it to a Logger instance

> [!IMPORTANT]
> This library is an internal component of CCPlugin that is used by the Java CC Proxy. The library is not directly used by Java CC Services code.

## Purpose

The primary purpose of this library is to provide a standardized way to capture, store, and manage log output within the CCPlugIn framework. This allows applications to:

- Capture console output from confidential VMs or processes
- Store log data in application-private files for later analysis
- Handle logging errors gracefully through Android's logging system
- Provide a consistent interface for log management across CCPlugIn components

## Components

### Logger

The `Logger` class provides functionality to create log files and write messages to them. It handles file creation and writing operations, with errors being logged to the Android log system.

Key features:
- Creates log files in the application's private file directory
- Appends messages to log files
- Handles I/O errors gracefully
- Uses Android context for file access

### Reader

The `Reader` class implements `Runnable` to read data from an input stream and post it to a logger. It's designed to be used in a separate thread to continuously read from an input stream (such as process output) and write the data to a logger for storage.

Key features:
- Implements Runnable for use in separate threads
- Continuously reads from input streams
- Writes each line of output to a Logger instance
- Handles thread interruption gracefully
- Logs errors using Android's logging system

## Thread Safety

The Logger class is not thread-safe. If multiple threads need to write to the same log file, external synchronization is required. Each Logger instance should be used by a single thread, or proper synchronization mechanisms should be implemented.

The Reader class is designed to be used in a single thread (as a Runnable), so thread safety is not a concern within the class itself.

## Error Handling

All I/O errors are caught and logged using Android's Log utility. This ensures that logging operations don't crash the application, while still providing visibility into any issues that may occur during logging operations.

For detailed API documentation, please refer to the generated Javadoc documentation.