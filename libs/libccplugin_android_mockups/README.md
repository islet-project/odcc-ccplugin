# Android Mockups library (libccplugin_android_mockups)

## Overview

This library provides Android Framework mockups that are used to run Android bound services inside a Realm Virtual Machine (VM) as part of the CCPlugIn framework. These mockups contain a limited set of Java classes from the Android Framework, enabling services to run in a Realm environment while maintaining compatibility with Android APIs.

The library is specifically designed for confidential computing environments where Android services need to run in isolated Realms while communicating with the main Android OS via RPC Binder through the CCPlugIn framework.

## Purpose

The primary purpose of this library is to enable Android services to run within a Realm environment by providing mock implementations of key Android Framework classes. This allows:

- Running Android bound services in a confidential Realm as part of CCPlugIn
- Maintaining API compatibility with standard Android services
- Supporting Java Binder and Parcelable data types for inter-process communication
- Enabling communication between a Realm and host OS via RPC Binder through CCPlugIn

## Key Features

### 1. Android Framework Mockups
The library provides mock implementations of core Android Framework classes including:
- `android.os.Binder` - Local implementation of IBinder for IPC
- `android.os.IBinder` - Base interface for remotable objects
- `android.os.Parcel` - Container for marshalled data
- `android.os.Parcelable` - Interface for parcelable objects
- `android.app.Service` - Base class for Android services
- `android.content.Context` - Interface to global information about an application environment
- `android.content.res.AssetManager` - Provides access to application assets

### 2. Realm VM Service Support
- Support for running Android bound services inside Realms
- Java Binder implementation for local IPC within the Realm
- Parcelable data types for efficient data serialization
- Asset management for accessing service resources

### 3. RPC Communication
- Communication with the main Android OS via RPC Binder
- Marshalling/unmarshalling of data between a Realm and host
- Support for standard Android IPC patterns

## Available Functionality

### Core Android IPC Components
1. **Binder/IBinder** - Full implementation of Android's Binder IPC mechanism
2. **Parcel/Parcelable** - Complete parceling system for data serialization
3. **Service** - Simplified Base service class
4. **Context** - Simplified application context with basic system services

### Asset Management
1. **AssetManager** - Access to application assets stored in `/mnt/apk/assets/`
2. **AssetFileDescriptor** - File descriptor for asset files
3. **ParcelFileDescriptor** - File descriptor for general file access

## Limitations

Due to the Realm VM environment and RPC-based communication, certain Android Framework functionality is not available or limited:

### 1. Security and Credentials
- **No credential access** - Cannot retrieve user credentials or process UIDs in a Realm context
- **Limited permission checking** - Security permissions cannot be enforced in the same way as on the host
- **No authentication** - Authentication mechanisms are not available across RPC boundary

### 2. File Descriptor Operations
- **No file descriptor passing** - Cannot send file descriptors via RPC Binder
- **Limited file operations** - File access is restricted to Realm filesystem
- **No direct file mapping** - Cannot directly map host files into a Realm VM

### 3. System Services
- **No system service access** - There is no access to Android system services like ActivityManager
- **No hardware access** - Direct hardware access is not possible
- **No advanced system APIs** - APIs requiring system-level permissions are not available

### 4. Process and Thread Management
- **No process control** - Cannot manage processes or retrieve process information
- **Limited thread operations** - Thread management is restricted
- **No inter-process synchronization** - Cannot use host-level synchronization primitives

### 5. Advanced Android Features
- **No UI components** - Activities, Views, and other UI elements are not available
- **No broadcast receivers** - Cannot receive system broadcasts
- **No content providers** - Content provider access is not supported
- **No notifications** - Notification system is not available
- **No background services** - Only bound services are supported

### 6. Network Operations
- **Limited network access** - Network operations may be restricted by the Realm VM configuration
- **No socket passing** - Cannot pass sockets via RPC Binder

## Usage

This library is automatically used when running Android services in a Realm VM environment. The mock implementations provide the necessary Android Framework APIs while ensuring compatibility with the VM's isolated environment.

Services should be implemented as standard Android bound services, extending the `android.app.Service` class and implementing the appropriate binder interface.

## Architecture

The library works by:
1. Providing mock implementations of Android Framework classes
2. Enabling services to use standard Android APIs within the Realm VM
3. Marshalling data through Parcel objects for RPC communication
4. Handling the translation between a Realm VM and host environments

## Security Considerations

- Services running in the Realm VM are isolated from the host OS
- There can be only one service running in a Realm VM
- Communication is limited to predefined RPC interfaces
- No direct access to host resources or credentials
- Data is marshalled through Binder RPC channels

### Service Lifecycle in CCPlugIn

1. **Realm VM Startup**:
   - Host app starts a Realm VM through VmManager API
   - The Realm VM boots the kernel, initrd and the Microdroid system image
   - The init process lanches the `Microdroid Manager` that loads and executes the `Microdroid Launcher`
   - The `Microdroid Launcher` loads the `NativeCCStub`
   - `NativeCCStub` initializes JVM with Android mockups
   - Service class is loaded from `/mnt/apk/assets/confidential-service.dex`

2. **Service Creation and Binding**:
   - Host calls `onBindForTargetService()` through RealmService interface
   - `NativeCCStub::onCreate()` is called to create an instance of the Service class
   - `NativeCCStub::onBind()` calls service's `onBind()` method on the Service's instance
   - Service returns its binder implementation
   - Binder is converted from Java to native AIBinder for RPC
   - the Binder RPC reference is returned to the host

3. **Method Invocation**:
   - Host calls AIDL methods on the Binder RPC reference returned by the `onBindForTargetService()`
   - Calls are forwarded through vsock Binder RPC to VM
   - Binder RPC and corresponding JNI layer invokes AIDL methods implemeneted by the Service
   - Results are marshalled back through the same path

