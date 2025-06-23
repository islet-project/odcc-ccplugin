// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include <android-base/expected.h>
#include <android-base/result.h>
#include <android/log.h>
#include <android/binder_ibinder_jni.h>
#include <binder/Status.h>

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/system_properties.h>
#include <unistd.h>
#include <vm_main.h>
#include <vm_payload.h>
#include <pthread.h>
#include <fstream>

#include <iostream>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <JniInvocation.h>
#include <android_util_Binder.h>
#include <android_os_Parcel.h>
#include <android_os_MessageQueue.h>
#include <com_islet_Cca.h>
#include "NativeCCStub.h"
#include "RealmServiceImpl.h"

using android::base::Result;
using android::binder::Status;
using std::string;
using ndk::ScopedAStatus;


#define CHECK_NULL(obj, msg, err)                                       \
    do {                                                                \
        if (obj == nullptr || env->ExceptionCheck()) {                  \
            __android_log_write(ANDROID_LOG_ERROR, TAG, msg);           \
            env->ExceptionDescribe();                                   \
            return android::base::MakeResultErrorWithCode(msg, err);    \
        }                                                               \
    } while(0)

#define CHECK_NULL_JNI(obj, msg, ...)                                   \
    do {                                                                \
        if (obj == nullptr || ctx.env->ExceptionCheck()) {              \
            __android_log_write(ANDROID_LOG_ERROR, TAG, msg);           \
            ctx.env->ExceptionDescribe();                               \
            return __VA_ARGS__;                                         \
        }                                                               \
    } while(0)

#define CHECK_NULL_JNI_RETURN_VOID(obj, msg, ...)                       \
    do {                                                                \
        if (obj == nullptr || ctx.env->ExceptionCheck()) {              \
            __android_log_write(ANDROID_LOG_ERROR, TAG, msg);           \
            ctx.env->ExceptionDescribe();                               \
            return;                                                     \
        }                                                               \
    } while(0)

#define CHECK_EXCEPTION_JNI(msg, ...)                                   \
    do {                                                                \
        if (ctx.env->ExceptionCheck()) {                                \
            __android_log_write(ANDROID_LOG_ERROR, TAG, msg);           \
            ctx.env->ExceptionDescribe();                               \
            return __VA_ARGS__;                                         \
        }                                                               \
    } while(0)

namespace android {
extern int register_android_os_MemoryFile(JNIEnv* env);
extern int register_com_android_internal_os_ClassLoaderFactory(JNIEnv *env);
}


namespace NativeCCStub {
constexpr char TAG[] = "NativeCCStub";

constexpr const char *MAIN_CLASS = "Main";
constexpr const char *INTENT_CLASS = "android/content/Intent";
constexpr const char *IBINDER_CLASS = "android/os/IBinder";

static std::string gServiceClassName;

static bool initializeServiceClassName() {
    std::ifstream file("/mnt/apk/assets/target_service.txt");
    if (!file.is_open()) {
        __android_log_write(ANDROID_LOG_ERROR, TAG, "Failed to open target_service.txt");
        return false;
    }

    std::string serviceName;
    std::getline(file, serviceName);
    file.close();

    // Remove any whitespace
    serviceName.erase(0, serviceName.find_first_not_of(" \t\n\r"));
    serviceName.erase(serviceName.find_last_not_of(" \t\n\r") + 1);

    if (serviceName.empty()) {
        __android_log_write(ANDROID_LOG_ERROR, TAG, "Empty service name in target_service.txt");
        return false;
    }

    gServiceClassName = serviceName;
    __android_log_print(ANDROID_LOG_INFO, TAG, "Initialized service class: %s", gServiceClassName.c_str());
    return true;
}

// Function to get the service class name
static const std::string& getServiceClassName() {
    return gServiceClassName;
}

template<typename T>
static inline ScopedAStatus from_result(const Result<T> &result)
{
    const auto &error = result.error();
    return ScopedAStatus::fromServiceSpecificErrorWithMessage(
        error.code(),
        error.message().c_str()
    );
}

static const char *jvm_argv[] =
    {
        "-Xbootclasspath:/apex/com.android.art/javalib/core-oj.jar:/apex/com.android.art/javalib/core-libart.jar:/apex/com.android.art/javalib/okhttp.jar:/apex/com.android.art/javalib/bouncycastle.jar:/apex/com.android.art/javalib/apache-xml.jar:/apex/com.android.i18n/javalib/core-icu4j.jar:/mnt/apk/assets/android-mockups.jar",
        "-Xms60m",
        "-Xmx60m",
        // Uncomment this option to make the JVM more verbose
        //"-verbose:class,collector,compiler,jni,monitor,signals,startup,third-party-jni,threads,verifier,verifier-debug,image,dex,interpreter",
        "-Djava.library.path=/mnt/apk/lib/x86_64/:/mnt/apk/lib/arm64-v8a/",
        "-cp",
        "/mnt/apk/assets/confidential-service.dex",
        nullptr};

struct LocalJniContext
{
    JNIEnv *env;

    jclass jThrowable;
    jmethodID jGetExceptionMessage;

    // ExampleService object and its methods
    jclass jClassExampleService;
    jmethodID jMethodExampleServiceCtor;
    jmethodID jMethodExampleServiceOnCreate;
    jmethodID jMethodExampleServiceOnBind;
    jmethodID jMethodExampleServiceOnUnbind;
    jmethodID jMethodExampleServiceOnDestroy;
    jobject jObjectExampleService;

    // Additional methods and objects for calling the above
    jclass jClassIntent;
    jmethodID jMethodIntentCtor;
    jobject jObjectIntent;

    // (IBinder) object and its methods

    jobject jObjectIBinder;
};

class JvmInstance
{
    JavaVM *gJavaVM = nullptr;

    JvmInstance(JavaVM *vm) :gJavaVM(vm) {}
public:
    ~JvmInstance() {
        if (gJavaVM)
            gJavaVM->DestroyJavaVM();
    }

    // Get the JavaVM instance
    JavaVM* getJavaVM() const {
        return gJavaVM;
    }

    static Result<std::unique_ptr<JvmInstance>> init(const char *jvm_argv[])
    {
        JavaVMInitArgs init_args;
        init_args.version = JNI_VERSION_1_6;
        init_args.ignoreUnrecognized = JNI_FALSE;
        std::vector<JavaVMOption> options;

        for (const char **ptr=jvm_argv; *ptr; ++ptr)
            options.push_back(JavaVMOption {*ptr});

        init_args.nOptions = options.size();
        init_args.options = options.data();
        JavaVM *vm;
        JNIEnv *env;

        if (JNI_CreateJavaVM(&vm, &env, &init_args) != JNI_OK) {
            __android_log_write(ANDROID_LOG_ERROR, TAG, "Failed to start JVM");
            return android::base::MakeResultErrorWithCode("Failed to start JVM", EFAULT);
        }

        return std::unique_ptr<JvmInstance>(new JvmInstance(vm));
    }

    Result<std::shared_ptr<LocalJniContext>> localContext()
    {
        // TODO: this context now holds state between lifecycle calls, if we don't have
        // guarantee that RPC Binder calls are in the same thread this might needs rethinking.
        static thread_local std::optional<std::shared_ptr<LocalJniContext>> ctx = {};

        if (ctx.has_value()) {
            __android_log_write(ANDROID_LOG_ERROR, TAG, "localContext(): found existing");
            return *ctx;
        }

        __android_log_write(ANDROID_LOG_ERROR, TAG, "localContext(): creating new");

        JNIEnv *env;
        // TODO: shouldn't this be called for each localContext() call?
        // I'm not sure we have guarantee that each RPC Binder call will be in the same thread.
        gJavaVM->AttachCurrentThread(&env, nullptr);

        // Registers android.os.* JNI/Java bindings for Binder, Parcel and Message Queue
        if (register_android_os_Binder(env) != JNI_OK) {
            const char *message = "Unable to register Binder classes";
            __android_log_write(ANDROID_LOG_FATAL, TAG, message);
            return android::base::MakeResultErrorWithCode(message, EFAULT);
        }

        if (android::register_android_os_Parcel(env) != JNI_OK) {
            const char *message = "Unable to register Parcel class";
            __android_log_write(ANDROID_LOG_FATAL, TAG, message);
            return android::base::MakeResultErrorWithCode(message, EFAULT);
        }

        if (android::register_android_os_MessageQueue(env) != JNI_OK) {
            const char *message = "Unable to register MessageQueue class";
            __android_log_write(ANDROID_LOG_FATAL, TAG, message);
            return android::base::MakeResultErrorWithCode(message, EFAULT);
        }

        if (android::register_android_os_MemoryFile(env) != JNI_OK) {
            const char *message = "Unable to register MemoryFile class";
            __android_log_write(ANDROID_LOG_FATAL, TAG, message);
            return android::base::MakeResultErrorWithCode(message, EFAULT);
        }

        if (android::register_com_android_internal_os_ClassLoaderFactory(env) != JNI_OK) {
            const char *message = "Unable to register ClassLoaderFactory class";
            __android_log_write(ANDROID_LOG_FATAL, TAG, message);
            return android::base::MakeResultErrorWithCode(message, EFAULT);
        }

        if (register_com_islet_Cca(env) != JNI_OK) {
            const char *message = "Unable to register Cca class";
            __android_log_write(ANDROID_LOG_FATAL, TAG, message);
            return android::base::MakeResultErrorWithCode(message, EFAULT);
        }

        jclass jThrowable = env->FindClass("java/lang/Throwable");
        CHECK_NULL(jThrowable, "Unable to locate class java.lang.Throwable", EEXIST);
        jmethodID jGetExceptionMessage = env->GetMethodID(jThrowable, "getMessage", "()Ljava/lang/String;");
        CHECK_NULL(jGetExceptionMessage, "Unable to locate java.lang.Throwable::getMessage() function", EEXIST);

        string jSignatureOnBind = string("(L") + INTENT_CLASS + ";)L" + IBINDER_CLASS + ";";
        string jSignatureOnUnbind = string("(L") + INTENT_CLASS + ";)Z";

        const std::string& serviceClassName = getServiceClassName();
        if (serviceClassName.empty()) {
            __android_log_write(ANDROID_LOG_ERROR, TAG, "Service class name is not initialized");
            return android::base::MakeResultErrorWithCode("Service class name is not initialized", EFAULT);
        }

        jclass jClassExampleService = env->FindClass(serviceClassName.c_str());
        CHECK_NULL(jClassExampleService, "Unable to locate service class", EEXIST);
        jmethodID jMethodExampleServiceCtor = env->GetMethodID(jClassExampleService, "<init>", "()V");
        CHECK_NULL(jMethodExampleServiceCtor, "Unable to locate ExampleService Ctor", EEXIST);
        jmethodID jMethodExampleServiceOnCreate = env->GetMethodID(jClassExampleService, "onCreate", "()V");
        CHECK_NULL(jMethodExampleServiceOnCreate, "Unabled to find method onCreate", EEXIST);
        jmethodID jMethodExampleServiceOnBind = env->GetMethodID(jClassExampleService, "onBind", jSignatureOnBind.c_str());
        CHECK_NULL(jMethodExampleServiceOnBind, "Unable to find method onBind", EEXIST);
        jmethodID jMethodExampleServiceOnUnbind = env->GetMethodID(jClassExampleService, "onUnbind", jSignatureOnUnbind.c_str());
        CHECK_NULL(jMethodExampleServiceOnUnbind, "Unable to find method onUnbind", EEXIST);
        jmethodID jMethodExampleServiceOnDestroy = env->GetMethodID(jClassExampleService, "onDestroy", "()V");
        CHECK_NULL(jMethodExampleServiceOnDestroy, "Unable to find method onDestroy", EEXIST);

        jclass jClassIntent = env->FindClass(INTENT_CLASS);
        CHECK_NULL(jClassIntent, "Unable to locate class Intent\n", EEXIST);
        jmethodID jMethodIntentCtor = env->GetMethodID(jClassIntent, "<init>", "()V");
        CHECK_NULL(jMethodIntentCtor, "Unable to locate Inter Ctor\n", EEXIST);

        ctx = std::make_shared<LocalJniContext>(
            env,

            jThrowable,
            jGetExceptionMessage,

            jClassExampleService,
            jMethodExampleServiceCtor,
            jMethodExampleServiceOnCreate,
            jMethodExampleServiceOnBind,
            jMethodExampleServiceOnUnbind,
            jMethodExampleServiceOnDestroy,
            nullptr,   // object instance, will be filled in the lifecycle calls

            jClassIntent,
            jMethodIntentCtor,
            nullptr,   // object instance, will be filled in the lifecycle calls

            nullptr
        );

        return *ctx;
    }
};

// Global JvmInstance variable
std::unique_ptr<JvmInstance> gJvmInstance;

int setupJvmInstance()
{
    static const char *env[][2] = {
        /* { "ANDROID_ROOT", "/data" }, */
        /* { "ANDROID_DATA", "/data" }, */
        {"ANDROID_I18N_ROOT", "/apex/com.android.i18n/" },
        {"ANDROID_ART_ROOT", "/apex/com.android.art"},
        {"ANDROID_TZDATA_ROOT", "/apex/com.android.tzdata"},
        { nullptr, nullptr }
    };

    for (std::size_t i=0; env[i][0]; ++i)
        setenv(env[i][0], env[i][1], 1);

    auto jvm_result = JvmInstance::init(jvm_argv);

    if (!jvm_result.has_value())
        return !from_result(jvm_result).isOk();
    gJvmInstance = std::move(jvm_result.value());

    return 0;
}

extern "C"
__attribute__((visibility("default")))
JavaVM* AndroidRuntimeGetJavaVM() {
    __android_log_write(ANDROID_LOG_ERROR, TAG, "AndroidRuntimeGetJavaVM is called");
    return gJvmInstance ? gJvmInstance->getJavaVM() : nullptr;
}

JNIEnv* getJNIEnv() {
    auto result = gJvmInstance->localContext();

    if (!result.has_value())
        return nullptr;

    auto &ctx = result.value();
    return ctx->env;
}

ScopedAStatus check_exception(const LocalJniContext &ctx)
{
    jthrowable exception = ctx.env->ExceptionOccurred();

    __android_log_write(ANDROID_LOG_INFO, TAG, "check_exception: start check_exception");

    if (!exception)
        return ScopedAStatus::ok();

    __android_log_write(ANDROID_LOG_INFO, TAG, "check_exception: found exception");
    jstring msg = static_cast<jstring>(ctx.env->CallObjectMethod(exception, ctx.jGetExceptionMessage));
    ScopedAStatus result;
    if (!msg) {
        const char *message = "Cannot fetch exception message";

        __android_log_write(ANDROID_LOG_ERROR, TAG, message);
        result = ScopedAStatus::fromExceptionCodeWithMessage(Status::EX_TRANSACTION_FAILED, message);
    } else {
        const char *exception_message = ctx.env->GetStringUTFChars(msg, nullptr);
        const auto message = string("Java exception occurred: ") + exception_message;

        __android_log_write(ANDROID_LOG_ERROR, TAG, message.c_str());
        result = ScopedAStatus::fromExceptionCodeWithMessage(Status::EX_TRANSACTION_FAILED, message.c_str());
    }
    __android_log_write(ANDROID_LOG_INFO, TAG, "check_exception: clear exception");

    ctx.env->ExceptionClear();
    __android_log_write(ANDROID_LOG_INFO, TAG, "check_exception: done");

    return result;
}

// perform_JNI function implementations
template<typename Ret>
ScopedAStatus perform_JNI(Ret *out, std::function<Ret(LocalJniContext &)> f)
{
    auto result = gJvmInstance->localContext();

    if (!result.has_value())
        return from_result(result);

    auto &ctx = result.value();
    Ret value = f(*ctx);
    auto status = check_exception(*ctx);

    if (status.isOk())
        *out = value;

    return status;
}

ScopedAStatus perform_JNI(std::function<void(LocalJniContext &)> f)
{
    auto result = gJvmInstance->localContext();

    __android_log_write(ANDROID_LOG_INFO, TAG, "perform_JNI: check result");
    if (!result.has_value())
        return from_result(result);

    __android_log_write(ANDROID_LOG_INFO, TAG, "perform_JNI: call function");
    auto &ctx = result.value();
    f(*ctx);

    __android_log_write(ANDROID_LOG_INFO, TAG, "perform_JNI: call check_exception");
    return check_exception(*ctx);
}

// Service lifecycle function implementations
ScopedAStatus onCreate()
{
    __android_log_write(ANDROID_LOG_INFO, TAG, "onCreate();");

    // NOTE: this is a workaround to android runtime loading mechanism that registers some methods needed
    // by the runtime. For example it is needed to convert JavaBinder objects into native AIBinder ones
    // (ibinderForJavaObject() is used by onBind() method implementation).
    // The function call registers our own methods instead of those provided by the android runtime lazy loading mechanism.
    AIBinder_setupRuntimeBindings((void *)&getJNIEnv,
            android::getibinderForJavaObjectPtr(),
            android::getjavaObjectForIBinderPtr(),
            android::getparcelForJavaObjectPtr());

    return perform_JNI([](LocalJniContext &ctx) {
            jobject jObjectExampleService = ctx.env->NewObject(ctx.jClassExampleService, ctx.jMethodExampleServiceCtor);
            CHECK_NULL_JNI(jObjectExampleService, "Unable to instantiate ExampleService");

            // Call onCreate() on Service - this will also trigger Dagger-Hilt and inject dependencies
            ctx.env->CallVoidMethod(jObjectExampleService, ctx.jMethodExampleServiceOnCreate);
            CHECK_EXCEPTION_JNI("Unable to call onCreate");

            ctx.jObjectExampleService = jObjectExampleService;
    });
}

ScopedAStatus onBind(::ndk::SpAIBinder* out)
{
    __android_log_write(ANDROID_LOG_INFO, TAG, "onBind();");

    if (out == nullptr) {
        return ScopedAStatus::fromServiceSpecificErrorWithMessage(1, "The out argument of ::ndk::SpAIBinder* type is nullptr");
    }

    auto result = gJvmInstance->localContext();

    if (!result.has_value())
        return from_result(result);

    auto &ctx = *result.value();

    jobject jObjectIntent = ctx.env->NewObject(ctx.jClassIntent, ctx.jMethodIntentCtor);
    if (jObjectIntent == nullptr || ctx.env->ExceptionCheck()) {
        __android_log_write(ANDROID_LOG_ERROR, TAG, "Cannot instantiate Intent");
        ctx.env->ExceptionDescribe();
            return ScopedAStatus::fromServiceSpecificErrorWithMessage(1, "Cannot instantiate Intent");
    }

    jobject jObjectIBinder = ctx.env->CallObjectMethod(ctx.jObjectExampleService, ctx.jMethodExampleServiceOnBind, jObjectIntent);
    if (jObjectIBinder == nullptr || ctx.env->ExceptionCheck()) {
        __android_log_write(ANDROID_LOG_ERROR, TAG, "Cannot call onBind");
        ctx.env->ExceptionDescribe();
        return ScopedAStatus::fromServiceSpecificErrorWithMessage(1, "Cannot call onBind");
    }

    ctx.jObjectIntent = jObjectIntent;
    ctx.jObjectIBinder = jObjectIBinder;

    AIBinder *nativeBinder = AIBinder_fromJavaBinder(ctx.env, jObjectIBinder);

    __android_log_print(ANDROID_LOG_ERROR, TAG, "onBind() returned Java Binder env = %p nativeBinder = %p javaBinder = %p\n", ctx.env, nativeBinder, jObjectIBinder);

    auto status = check_exception(ctx);

    out->set(nativeBinder);

    return status;
}

ScopedAStatus onUnbind()
{
    __android_log_write(ANDROID_LOG_INFO, TAG, "onUnbind();");
    return perform_JNI([](const LocalJniContext &ctx) {
            jboolean ignored = ctx.env->CallBooleanMethod(ctx.jObjectExampleService, ctx.jMethodExampleServiceOnUnbind, ctx.jObjectIntent);
            CHECK_EXCEPTION_JNI("Unable to call onUnbind");
    });
}

ScopedAStatus onDestroy()
{
    __android_log_write(ANDROID_LOG_INFO, TAG, "onDestroy();");
    return perform_JNI([](const LocalJniContext &ctx) {
            ctx.env->CallVoidMethod(ctx.jObjectExampleService, ctx.jMethodExampleServiceOnDestroy);
            CHECK_EXCEPTION_JNI("Unable to call onDestroy");
    });
}

Result<void> start_service()
{
    auto service = ndk::SharedRefBase::make<RealmServiceImpl>();

    auto realmBinder = service->asBinder();
    if (realmBinder == nullptr) {
        __android_log_write(ANDROID_LOG_ERROR, TAG, "Failed to get binder from RealmServiceImpl");
        return android::base::MakeResultErrorWithCode("Failed to get binder from RealmServiceImpl", EFAULT);
    }

    __android_log_print(ANDROID_LOG_ERROR, TAG, "start_service() using RealmServiceImpl binder: %p\n", realmBinder.get());

    auto callback = []([[maybe_unused]] void* param) { AVmPayload_notifyPayloadReady(); };
    AVmPayload_runVsockRpcServer(realmBinder.get(), service->PORT, callback,
                                 nullptr);

    return {};
}
} // namespace NativeCCStub

extern "C" int AVmPayload_main()
{
    __android_log_write(ANDROID_LOG_INFO, NativeCCStub::TAG, "Hello from AVmPayload_main");

    if (!NativeCCStub::initializeServiceClassName()) {
        __android_log_write(ANDROID_LOG_ERROR, NativeCCStub::TAG, "Failed to initialize service class name");
        return 1;
    }

    __system_property_set("debug.microdroid.app.run", "true");

    static JniInvocation jni_invocation;
    if (!jni_invocation.Init(nullptr)) {
        __android_log_write(ANDROID_LOG_ERROR, NativeCCStub::TAG, "Failed to initialize JNI invocation API");
        return 1;
    }

    if (NativeCCStub::setupJvmInstance()) {
        __android_log_write(ANDROID_LOG_ERROR, NativeCCStub::TAG, "Cannot initialize JvmInstance!");
        return 1;
    }

    auto res = NativeCCStub::start_service();

    if (res.ok()) {
        return 0;
    } else {
        __android_log_write(ANDROID_LOG_ERROR, NativeCCStub::TAG, res.error().message().c_str());
        return 1;
    }
}
