# CCPlugin Libraries

This document describes each library in the CCPlugIn project. CCPlugIn enables running Java services in an Arm CCA Realm environment on Android, bridging the Normal World (host Android) and the Realm World.

## Library Overview

| Library | Language | Runs In | Purpose |
|---------|----------|---------|---------|
| libccplugin_islet_realm | Java | Realm VM | Arm CCA API for confidential services |
| libccplugin_islet_android | Java | Host Android | a dummy/stub implementation of the Cca Java library for Android development |
| libccplugin_android_mockups | Java | Realm VM | Minimal Android framework APIs for Realm World |
| libccplugin_native | C++ | Realm VM | Native payload: JVM launcher and Binder bridge |
| libccplugin_jni | C/C++ | Realm VM | JNI bindings for Binder, Parcel, etc. |
| libccplugin_vm | Java | Host Android | Virtual machine lifecycle management |
| libccplugin_log | Java | Host Android, Realm VM | Utilities for VM related logging |

### When Each Library Is Required

**Always required** when applying CCPlugIn to your app to run your service in Realm:
- `libccplugin_vm`, `libccplugin_log`, `libccplugin_native`, `libccplugin_android_mockups` — Host app and Realm payload cannot run without these.
- `libccplugin_jni` — Statically linked into `libccplugin_native`; not declared directly by the app.
- `libccplugin_islet_realm` — Bundled with `libccplugin_android_mockups`. Required for Realm VM.

**Optional:**
- `libccplugin_islet_android` — a dummy/stub implementation of the Cca Java library for Android development, which will be replaced by the proper Islet functionality (libccplugin_islet_realm) when ported to CC.

For how to apply CCPlugIn to your repository, please see [How to apply CCPlugIn into your repository](../README.md#how-to-apply-ccplugin-into-your-repository) section.

### Java API support for CC services

A CC service developer can utilize a standard Java API available in Android 15, which is aligned with OpenJDK 17. This includes core packages such as:

- `java.lang` - Core Java classes including Object, String, Thread, Runnable, and more
- `java.util` - Collections framework, including List, Map, Set, and utility classes
- `java.io` - Basic I/O operations for file and stream handling
- `java.net` - Network operations and URL handling
- `java.time` - Date and time API (JSR-310)
- `java.math` - Mathematical operations including BigDecimal and BigInteger
- `java.nio` - Buffer operations and NIO utilities
- `java.text` - Text processing and formatting
- `java.security` - Security-related classes including MessageDigest and SecureRandom
- `java.util.concurrent` - Concurrency utilities and thread management
- `java.util.function` - Functional interfaces for lambda expressions
- `java.util.regex` - Regular expression support
- `java.util.stream` - Stream API for functional-style operations on collections
- `javax.crypto` - Cryptographic operations
- `javax.net.ssl` - SSL/TLS support

Note that this is not a complete implementation of the OpenJDK 17 API but a subset that is commonly used in Android services.
