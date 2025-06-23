// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include <android/log.h>
#include <jni.h>
#include <vm_payload.h>
#include <android/binder_ibinder_jni.h>

#include <string>

#define MAX_VM_INSTANCE_SECRET_SIZE 32

static const char * const TAG = "islet_cca";
static const char * const CCA_CLASS_NAME = "com/islet/Cca";

extern "C" JNIEXPORT jstring JNICALL
Java_com_islet_Cca_getEncryptedStoragePath(__unused JNIEnv *env,
                                           __unused jclass clazz) {
    const char *path = AVmPayload_getEncryptedStoragePath();

    if (path != nullptr)
        return env->NewStringUTF(path);

    return nullptr;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_islet_Cca_getApkContentsPath(__unused JNIEnv *env,
                                               __unused jclass clazz) {
    const char *path = AVmPayload_getApkContentsPath();

    if (path != nullptr)
        return env->NewStringUTF(path);

    return nullptr;
}

static jobject construct_AttestationResult(JNIEnv *env,
                                           enum AVmAttestationStatus status,
                                           jbyteArray java_evidence_array)
{
    jclass result_class = env->FindClass(std::string(CCA_CLASS_NAME).append("$AttestationResult").c_str());
    jclass status_enum_class = env->FindClass(std::string(CCA_CLASS_NAME).append("$AttestationStatus").c_str());

    if (result_class == nullptr || status_enum_class == nullptr) {
        __android_log_write(ANDROID_LOG_FATAL, TAG, "Cannot find AttestationResult or AttestationStatus classes");
        return nullptr;
    }

    std::string constructor_sig = "(L" + std::string(CCA_CLASS_NAME) + "$AttestationStatus;[B)V";
    jmethodID result_constructor = env->GetMethodID(result_class, "<init>", constructor_sig.c_str());

    if (result_constructor == nullptr) {
        __android_log_write(ANDROID_LOG_FATAL, TAG, "Cannot find AttestationResult constructor");
        return nullptr;
    }

    jfieldID status_field_id;
    switch (status) {
        case ATTESTATION_OK:
            status_field_id = env->GetStaticFieldID(status_enum_class, "OK", ("L" + std::string(CCA_CLASS_NAME) + "$AttestationStatus;").c_str());
            break;
        case ATTESTATION_ERROR_INVALID_CHALLENGE:
            status_field_id = env->GetStaticFieldID(status_enum_class, "ERROR_INVALID_CHALLENGE", ("L" + std::string(CCA_CLASS_NAME) + "$AttestationStatus;").c_str());
            break;
        case ATTESTATION_ERROR_ATTESTATION_FAILED:
            status_field_id = env->GetStaticFieldID(status_enum_class, "ERROR_ATTESTATION_FAILED", ("L" + std::string(CCA_CLASS_NAME) + "$AttestationStatus;").c_str());
            break;
        case ATTESTATION_ERROR_UNSUPPORTED:
            status_field_id = env->GetStaticFieldID(status_enum_class, "ERROR_UNSUPPORTED", ("L" + std::string(CCA_CLASS_NAME) + "$AttestationStatus;").c_str());
            break;
        default:
            __android_log_print(ANDROID_LOG_FATAL, TAG, "Unsupported attestation status %d\n", status);
            return nullptr;
    }

    jobject java_status = env->GetStaticObjectField(status_enum_class, status_field_id);

    return env->NewObject(result_class, result_constructor, java_status, java_evidence_array);
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_islet_Cca_requestAttestation(JNIEnv *env,
                                      __unused jclass clazz,
                                      jbyteArray challenge) {

    if (challenge == nullptr) {
        return construct_AttestationResult(env, ATTESTATION_ERROR_INVALID_CHALLENGE, nullptr);
    }

    jbyte* challenge_array = env->GetByteArrayElements(challenge, nullptr);
    size_t challenge_size = env->GetArrayLength(challenge);

    uint8_t *evidence = nullptr;
    size_t evidence_size;

    AVmAttestationStatus status = AVmPayload_requestArmCcaAttestation((void *)challenge_array, challenge_size,
                                                                      (void **)&evidence, &evidence_size);

    jbyteArray java_evidence_array = nullptr;
    if (status == AVmAttestationStatus::ATTESTATION_OK && evidence != nullptr && evidence_size > 0) {
        java_evidence_array = env->NewByteArray(evidence_size);
        if (java_evidence_array == nullptr) {
            __android_log_write(ANDROID_LOG_FATAL, TAG, "Cannot allocate memory for attestation evidence");
            env->ReleaseByteArrayElements(challenge, challenge_array, JNI_ABORT);
            free(evidence);
            return nullptr;
        }
        env->SetByteArrayRegion(java_evidence_array, 0, evidence_size, reinterpret_cast<const jbyte*>(evidence));
    }

    env->ReleaseByteArrayElements(challenge, challenge_array, JNI_ABORT);

    if (evidence) {
        free(evidence);
    }

    return construct_AttestationResult(env, status, java_evidence_array);
}

static jobject construct_MeasurementExtendStatus(JNIEnv *env,
                                           enum AVmMeasurementExtendStatus status)
{
    jclass status_enum_class = env->FindClass(std::string(CCA_CLASS_NAME).append("$MeasurementExtendStatus").c_str());
    if (status_enum_class == nullptr) {
        __android_log_write(ANDROID_LOG_FATAL, TAG, "Cannot find MeasurementExtendStatus class");
        return nullptr;
    }

    const char* status_field_name;
    switch (status) {
        case AVmMeasurementExtendStatus::MEASUREMENT_EXTEND_OK:
                status_field_name = "OK";
                break;
        case AVmMeasurementExtendStatus::MEASUREMENT_EXTEND_ERROR_INVALID_MEASUREMENT:
                status_field_name = "ERROR_INVALID_MEASUREMENT";
                break;
        case AVmMeasurementExtendStatus::MEASUREMENT_EXTEND_ERROR_FAILED_TO_EXTEND_ARM_CCA_REM_SLOT:
                status_field_name = "ERROR_FAILED_TO_EXTEND_ARM_CCA_REM_SLOT";
                break;
        case AVmMeasurementExtendStatus::MEASUREMENT_EXTEND_ERROR_UNSUPPORTED:
                status_field_name = "ERROR_UNSUPPORTED";
                break;
        default:
            __android_log_print(ANDROID_LOG_FATAL, TAG, "Unsupported measurement extend status %d\n", status);
            return nullptr;
    }

    std::string status_sig = "L" + std::string(CCA_CLASS_NAME) + "$MeasurementExtendStatus;";
    jfieldID status_field_id = env->GetStaticFieldID(status_enum_class, status_field_name, status_sig.c_str());

    return env->GetStaticObjectField(status_enum_class, status_field_id);
}


extern "C" JNIEXPORT jobject JNICALL
Java_com_islet_Cca_measurementExtend(JNIEnv *env,
                                     __unused jclass clazz,
                                     jobject index,
                                     jbyteArray measurement)
{
    if (index == nullptr) {
        return construct_MeasurementExtendStatus(env, AVmMeasurementExtendStatus::MEASUREMENT_EXTEND_ERROR_FAILED_TO_EXTEND_ARM_CCA_REM_SLOT);
    }

    if (measurement == nullptr) {
        return construct_MeasurementExtendStatus(env, AVmMeasurementExtendStatus::MEASUREMENT_EXTEND_ERROR_INVALID_MEASUREMENT);
    }

    jclass enum_class = env->FindClass("java/lang/Enum");
    if (enum_class == nullptr) {
        __android_log_write(ANDROID_LOG_FATAL, TAG, "Cannot find java.lang.Enum class");
        return nullptr;
    }

    jmethodID ordinal_method = env->GetMethodID(enum_class, "ordinal", "()I");
    jint slot_ordinal = env->CallIntMethod(index, ordinal_method);
    AVmMeasurementSlotIndex slot = static_cast<AVmMeasurementSlotIndex>(slot_ordinal);

    jbyte* measurement_array = env->GetByteArrayElements(measurement, nullptr);
    size_t measurement_len = env->GetArrayLength(measurement);

    AVmMeasurementExtendStatus status = AVmPayload_measurementExtend(slot, (void *)measurement_array, measurement_len);

    env->ReleaseByteArrayElements(measurement, measurement_array, JNI_ABORT);

    return construct_MeasurementExtendStatus(env, status);
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_islet_Cca_getVmInstanceSecret(JNIEnv *env,
                                       __unused jclass clazz,
                                       jbyteArray identifier,
                                       jint secret_size)
{
    if (secret_size > MAX_VM_INSTANCE_SECRET_SIZE || identifier == nullptr) {
        return nullptr;
    }

    jbyte* identifier_ptr = env->GetByteArrayElements(identifier, nullptr);
    size_t identifier_size = env->GetArrayLength(identifier);

    jbyteArray java_secret_array = env->NewByteArray(secret_size);
    if (java_secret_array == nullptr) {
        __android_log_write(ANDROID_LOG_FATAL, TAG, "Cannot allocate memory for vm instance secret");
        env->ReleaseByteArrayElements(identifier, identifier_ptr, JNI_ABORT);
        return nullptr;
    }

    jbyte* java_secret_ptr = env->GetByteArrayElements(java_secret_array, nullptr);

    AVmPayload_getVmInstanceSecret((void*)identifier_ptr, identifier_size, (void*)java_secret_ptr, secret_size);

    env->ReleaseByteArrayElements(java_secret_array, java_secret_ptr, 0);
    env->ReleaseByteArrayElements(identifier, identifier_ptr, JNI_ABORT);

    return java_secret_array;
}

static jobject construct_StartProvisioningStatus(JNIEnv *env,
                                           enum AVmStartProvisioningStatus status)
{
    jclass status_enum_class = env->FindClass(std::string(CCA_CLASS_NAME).append("$StartProvisioningStatus").c_str());
    if (status_enum_class == nullptr) {
        __android_log_write(ANDROID_LOG_FATAL, TAG, "Cannot find StartProvisioningStatus class");
        return nullptr;
    }

    const char* status_field_name;
    switch (status) {
        case AVmStartProvisioningStatus::PROVISIONING_START_OK:
                status_field_name = "OK";
                break;
        case AVmStartProvisioningStatus::PROVISIONING_ERROR_INVALID_PARAMS:
                status_field_name = "ERROR_INVALID_PARAMS";
                break;
        case AVmStartProvisioningStatus::PROVISIONING_ERROR_UNSUPPORTED:
                status_field_name = "ERROR_UNSUPPORTED";
                break;
        default:
            __android_log_print(ANDROID_LOG_FATAL, TAG, "Unsupported start provisioning status %d\n", status);
            return nullptr;
    }

    std::string status_sig = "L" + std::string(CCA_CLASS_NAME) + "$StartProvisioningStatus;";
    jfieldID status_field_id = env->GetStaticFieldID(status_enum_class, status_field_name, status_sig.c_str());

    return env->GetStaticObjectField(status_enum_class, status_field_id);
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_islet_Cca_startProvisioning(JNIEnv *env,
                                       __unused jclass clazz,
                                       jstring url,
                                       jstring caCertPath,
                                       jstring destination,
                                       jobject callback)
{
    const char *url_str = env->GetStringUTFChars(url, 0);
    const char *ca_cert_path_str = env->GetStringUTFChars(caCertPath, 0);
    const char *destination_str = env->GetStringUTFChars(destination, 0);
    AIBinder *nativeBinderCallback = AIBinder_fromJavaBinder(env, callback);

    AVmStartProvisioningStatus status = AVmPayload_startProvisioning(url_str, ca_cert_path_str, destination_str, nativeBinderCallback);

    // Release the UTF string characters to prevent memory leaks
    env->ReleaseStringUTFChars(url, url_str);
    env->ReleaseStringUTFChars(caCertPath, ca_cert_path_str);
    env->ReleaseStringUTFChars(destination, destination_str);

    return construct_StartProvisioningStatus(env, status);
}


extern "C" int register_com_islet_Cca(JNIEnv* env) {
    jclass bridgeClass = env->FindClass(CCA_CLASS_NAME);
    if (bridgeClass == nullptr) {
        __android_log_write(ANDROID_LOG_FATAL, TAG, "Failed to find com.islet.Cca class");
        return JNI_ERR;
    }

    JNINativeMethod methods[] = {
        { "getEncryptedStoragePath", "()Ljava/lang/String;", (void*)Java_com_islet_Cca_getEncryptedStoragePath },
        { "getApkContentsPath", "()Ljava/lang/String;", (void*)Java_com_islet_Cca_getApkContentsPath },
        { "requestAttestation", "([B)Lcom/islet/Cca$AttestationResult;", (void*)Java_com_islet_Cca_requestAttestation },
        { "measurementExtend", "(Lcom/islet/Cca$MeasurementSlotIndex;[B)Lcom/islet/Cca$MeasurementExtendStatus;", (void*)Java_com_islet_Cca_measurementExtend },
        { "getVmInstanceSecret", "([BI)[B", (void*)Java_com_islet_Cca_getVmInstanceSecret },
        { "startProvisioning", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Landroid/system/virtualization/payload/IProvisioningCallback;)Lcom/islet/Cca$StartProvisioningStatus;" , (void*)Java_com_islet_Cca_startProvisioning }
    };

    jint result = env->RegisterNatives(bridgeClass, methods, sizeof(methods) / sizeof(methods[0]));
    if (result != JNI_OK) {
        __android_log_print(ANDROID_LOG_FATAL, TAG, "Failed to register native methods for com.islet.Cca class (result = %d)", result);
        return result;
    }

    return JNI_OK;
}
