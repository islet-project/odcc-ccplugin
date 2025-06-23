// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package com.islet;

import java.lang.String;
import java.util.ArrayList;
import java.lang.Enum;

import android.system.virtualization.payload.IProvisioningCallback;
import android.system.virtualization.payload.ProvisioningError;

/**
 * An Islet utility class that provides Arm Confidential Compute functionality.
 */
public class Cca {

    /**
     * The status of Arm CCA attestation request operation.
     */
    public enum AttestationStatus {
        /** The remote attestation completes successfully. */
        OK,

        /** The challenge size is not between 0 and 64. */
        ERROR_INVALID_CHALLENGE,

        /** Failed to attest the VM. */
        ERROR_ATTESTATION_FAILED,

        /** Remote attestation is not supported in the current environment. */
        ERROR_UNSUPPORTED
    }

    /**
     * The status of Arm CCA measurement extend.
     */
    public enum MeasurementExtendStatus {
        /** The measurement extend operation completes successfully. */
        OK,

        /** The measurement size is invalid. */
        ERROR_INVALID_MEASUREMENT,

        /** Failed to extend the REM slot. */
        ERROR_FAILED_TO_EXTEND_ARM_CCA_REM_SLOT,

        /** Measurement extend is not supported in the current environment. */
        ERROR_UNSUPPORTED
    }

    /**
     * The status of the remote provisioning start operation
     */
    public enum StartProvisioningStatus {
        /** The operation started successfully. */
        OK,

        /** The provided parameters are invalid. */
        ERROR_INVALID_PARAMS,

        /** The operation is not supported in the current environment. */
        ERROR_UNSUPPORTED
    }

    /**
     * The measurement slot index.
     */
    public enum MeasurementSlotIndex {
        /**
         * Realm Initial Measurement. This slot cannot be used in measurement extend operation.
         */
        RIM,

        /** Realm Extensible Measurement Slot 0 */
        REM0,

        /** Realm Extensible Measurement Slot 1 */
        REM1,

        /** Realm Extensible Measurement Slot 2 */
        REM2,

        /** Realm Extensible Measurement Slot 3 */
        REM3,
    }

    /**
     * A class representing the status of Arm CCA attestation request operation.
     */
    public static final class AttestationResult {
        /** The status of the operation */
        public final AttestationStatus status;
        /**
         * The buffer containing the attestation evidence.
         * It is valid only if the operation was successful (isSuccess() == true).
         */
        public final byte[] data;

        public AttestationResult(AttestationStatus status, byte[] data) {
            this.status = status;
            this.data = data;
        }

        public boolean isSuccess() {
            return status == AttestationStatus.OK;
        }
    }

    /**
     * Gets the path to the encrypted persistent storage for the VM, if any. This is
     * a directory under which any files or directories created will be stored on
     * behalf of the VM by the host app. All data is encrypted using a key known
     * only to the VM, so the host cannot decrypt it, but may delete it.
     *
     * @return the path to the encrypted storage directory, or {@code null} if no encrypted
     * storage was requested in the VM configuration. The string remains valid
     * for the lifetime of the VM.
     */
    public static native String getEncryptedStoragePath();

    /**
     * Gets the path to the APK contents. It is a directory, under which are
     * the unzipped contents of the APK containing the payload, all read-only
     * but accessible to the payload.
     *
     * @return the path to the APK contents or {@code null} if such a path doesn't exist.
     * The string remains valid for the lifetime of the VM.
     */
    public static native String getApkContentsPath();

    /**
     * Requests the Arm CCA remote attestation token. For more details
     * about the token format, please refer to the Realm Management Monitor specification
     * https://developer.arm.com/documentation/den0137/latest/
     *
     * The challenge will be included in the Realm attestation token,
     * serving as proof of the freshness of the result.
     *
     * @param challenge A pointer to the challenge buffer (64 bytes)
     * @return an instance of {@code AttestationResult}
     */
    public static native AttestationResult requestAttestation(byte[] challenge);

    /**
     * Extends the Arm CCA REM slot.
     *
     * The measurement will be used to extend a specific Realm Extensible Measurement (REM) slot.
     * The measurements are reflected in the Arm CCA attestation token (attestation evidence).
     * For more information about measurement extend operation, please refer to
     * Realm Management Monitor specification https://developer.arm.com/documentation/den0137/latest/
     *
     * @param index The {@code MeasurementSlotIndex} of REM slot
     * @param measurement pointer to the measurement buffer (<= 64 bytes)
     *
     * @return an instance of {@code MeasurementExtendStatus}
     */
    public static native MeasurementExtendStatus measurementExtend(MeasurementSlotIndex index, byte[] measurement);

    /**
     * Returns all or part of a 32-byte secret that is bound to this unique VM
     * instance and the supplied identifier. The secret can be used, for example, as an
     * encryption key.
     *
     * Every VM has a secret that is derived from a device-specific value known to
     * the Realm Management Monitor (Arm CCA), the code that runs in the VM, and
     * its non-modifiable configuration; it is not made available to the host OS.
     *
     * This function performs a further derivation from the VM secret and the
     * supplied identifier. As long as the VM identity doesn't change, the same value
     * will be returned for the same identifier, even if the VM is stopped
     * and restarted or the device rebooted.
     *
     * If multiple secrets are required for different purposes, a different
     * identifier should be used for each. The identifiers are otherwise arbitrary
     * byte sequences and do not need to be kept secret; typically, they are
     * hardcoded in the calling code.
     *
     * @param identifier identifier of the secret to return.
     * @param secret_size number of bytes of the secret to get, <= 32.
     * @return VM instance secret
     */
    public static native byte[] getVmInstanceSecret(byte[] identifier, int secret_size);


    /**
     * Starts provisioning of the resource located at url to the destination path. During the provisioning
     * process, the confidential service acts as a client that establishes a secure channel via HTTPS/RA-TLS
     * with the external provisioning server. During the TLS negotiation phase, the provisioning client
     * presents the attestation evidence (Arm CCA attestation token) to the provisioning server, which
     * checks its content using the attestation verification service. Once the verification of the attestation
     * token succeeds, the TLS secure channel is established and the client can download a file from the provisioning
     * server.
     *
     * The caCertPath is used to authenticate the provisioning server.
     *
     * <p>The callback parameter must implement the {@link IProvisioningCallback} interface, which provides
     * two methods:
     * <ul>
     * <li>{@link IProvisioningCallback#onError(byte)} - Called when an error occurs during provisioning</li>
     * <li>{@link IProvisioningCallback#onSuccess(String, String)} - Called when provisioning completes successfully</li>
     * </ul>
     *
     * @param url of the provisioned resource
     * @param caCertPath the relative path to the Root CA Certificate used to authenticate the provisioning server
     *                   Note that it is relative to <apk root path>/assets folder.
     * @param destination the relative path of the downloaded file. The path is relative to encryptedstore mountpoint.
     * @param callback The reference to the implementation of IProvisioningCallback.Stub used to notify the client
     *                 about the status of the operation
     * @return Status of the call {@code StartProvisioningStatus}
     */
    public static native StartProvisioningStatus startProvisioning(String url, String caCertPath, String destination, IProvisioningCallback callback);
}
