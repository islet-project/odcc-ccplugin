// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package com.islet;

import java.lang.String;
import java.util.ArrayList;
import java.lang.Enum;

import android.os.IBinder;

public class Cca {

    public enum AttestationStatus {
        /** The remote attestation completes successfully. */
        OK,

        /** The challenge size is not between 0 and 64. */
        ERROR_INVALID_CHALLENGE,

        /** Failed to attest the VM. Please retry at a later time. */
        ERROR_ATTESTATION_FAILED,

        /** Remote attestation is not supported in the current environment. */
        ERROR_UNSUPPORTED
    }

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
        /** The operation started sucessfully. */
        OK,

        /** The provided parameters are invalid. */
        ERROR_INVALID_PARAMS,

        /** The operation is not supported in the current environment. */
        ERROR_UNSUPPORTED
    }

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

    public static final class AttestationResult {
        public final AttestationStatus status;
        public final byte[] data;

        public AttestationResult(AttestationStatus status, byte[] data) {
            this.status = status;
            this.data = data;
        }

        public boolean isSuccess() {
            return status == AttestationStatus.OK;
        }
    }

    public static String getEncryptedStoragePath() {
        return null;
    }

    public static String getApkContentsPath() {
        return null;
    }

    public static AttestationResult requestAttestation(byte[] challenge) {
        return new AttestationResult(AttestationStatus.ERROR_UNSUPPORTED, null);
    }

    public static MeasurementExtendStatus measurementExtend(MeasurementSlotIndex index, byte[] measurement) {
        return MeasurementExtendStatus.ERROR_UNSUPPORTED;
    }

    public static byte[] getVmInstanceSecret(byte[] identifier, int secret_size) {
        return null;
    }

    public static StartProvisioningStatus startProvisioning(String url, String caCertPath, String destination, IBinder callback) {
        return StartProvisioningStatus.ERROR_UNSUPPORTED;
    }
}
