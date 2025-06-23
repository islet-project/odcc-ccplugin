# Islet CCA Java API (libccplugin_islet_realm)

## Overview

This library provides Java bindings for Arm Confidential Compute Architecture (CCA) functionality within the CCPlugIn framework. It enables confidential computing services running in Islet realms to access security-sensitive operations such as remote attestation, measurement extension, secure storage, and remote provisioning.

The library serves as a bridge between Java-based confidential services and the native Islet CCA implementation, allowing developers to leverage Arm CCA features while writing services in Java.

## Purpose

The primary purpose of this library is to expose Arm CCA functionality to Java services running in confidential Realm VMs as part of the CCPlugIn framework. This allows services to:

- Request attestation tokens carrying attestation evidence
- Extend realm measurements reflected in attestation evidence
- Access instance-bound secrets for encryption
- Utilize encrypted persistent storage
- Perform secure remote provisioning of resources

## Key Features

### 1. Remote Attestation
- Request Arm CCA remote attestation tokens
- Include freshness challenges in attestation evidence
- Verify Realm integrity and configuration

### 2. Measurement Extension
- Extend Realm Extensible Measurement (REM) slots
- Incorporate custom measurements into attestation evidence
- Support for multiple measurement slots (REM0-REM3)

### 3. Realm VM Instance Secrets
- Derive encryption keys bound to unique Realm VM instances and a unique Realm Sealing Key
- Generate up to 32-byte secrets for cryptographic operations
- Support for multiple secrets with different identifiers

### 4. Encrypted Storage
- Access encrypted persistent storage paths
- The stored data on the disk is encrypted using specific keys derived from the instance secret and a unique Realm Sealing Key

### 5. Remote Provisioning
- Securely download resources from remote servers after successful remote attestation procedure
- Establish RA-TLS (Remote Attestation combined with TLS) connections with provisioning servers

## Usage

This library is automatically available to confidential services running in Islet realms within the CCPlugIn framework. Services can directly call the static methods provided by the `Cca` class to access Arm CCA functionality.

For detailed API documentation, please refer to the generated Javadoc documentation.