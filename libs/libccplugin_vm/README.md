# VM library (libccplugin_vm)

## Overview

This library runs on **Host Android** and manages the **Realm** (aka, confidential virtual machine) lifecycle for CCPlugIn. It builds a `VirtualMachineConfig` from application assets (`assets/vm_configs/vm_config.json`), starts the VM through Android’s `VirtualMachineManager`, and when the payload is ready connects to `IRealmService` over vsock (same port as defined for the Realm service AIDL). Optional debug mode can capture VM console and log output via `Reader` into local files.

It is the host-side counterpart to the Realm payload (`libccplugin_native`, mockups, and confidential service): the auto-generated **`CCProxyService`** uses `VmManager` to bring up the VM and obtain an `IRealmService` handle for forwarding AIDL calls into the confidential runtime.

## Purpose

The primary purpose of this library is to own confidential VM lifecycle on the host application side within the CCPlugIn framework. This allows the host to:

- Start and configure the confidential VM from the host application
- Receive asynchronous notification when the Realm binder is available (`VmServiceCallback`)
- Expose `IRealmService` for proxy/stub code once vsock connectivity is established

## Usage

In normal integration you **do not** instantiate `VmManager` in application code: **CCPlugIn emits `CCProxyService`**, and that generated service uses `VmManager` internally to start the VM, wait for vsock/`IRealmService`, and bridge stubs and proxies. If you maintain a fork or custom generator output, use the same pattern inside your host-side proxy service and register a `VmServiceCallback` only where you must react to readiness or connection errors.

For detailed API documentation, please refer to the generated Javadoc documentation.
