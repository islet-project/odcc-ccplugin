/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IExampleInterface.aidl
 */

/*
 * Copyright 2021 The Android Open Source Project
 * Copyright (c) 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include <aidl/com/examplecc/service/IResponse.h>
#include <aidl/com/islet/binder/service/BnRealmService.h>
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

#include <iostream>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <jni.h>
#include <JniInvocation.h>
#include <android_util_Binder.h>
#include <android_os_Parcel.h>
#include <android_os_MessageQueue.h>
using aidl::com::examplecc::service::IResponse;

using aidl::com::islet::binder::service::BnRealmService;
using android::base::Result;
using android::binder::Status;
using std::string;
using ndk::ScopedAStatus;
struct IResponsePeer {
    std::shared_ptr<IResponse> iface;
};


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


namespace {
constexpr char TAG[] = "payload";
constexpr const char *EXAMPLE_SERVICE_CLASS = "com/examplecc/service/ExampleService";
constexpr const char *IEXAMPLE_INTERFACE_CLASS = "com/examplecc/service/IExampleInterface$Stub";

constexpr const char *MAIN_CLASS = "Main";
constexpr const char *INTENT_CLASS = "android/content/Intent";
constexpr const char *IBINDER_CLASS = "android/os/IBinder";

static string convertJStringToString(JNIEnv* env, jstring jmsg) {
    string msg = "";
    if (jmsg) {
        const char* cstr = env->GetStringUTFChars(jmsg, nullptr);
        if (cstr) {
            msg.assign(cstr);
            env->ReleaseStringUTFChars(jmsg, cstr);
        }
    }
    return msg;
}

static void handleScopedAStatusError(JNIEnv* env, const ScopedAStatus& status, const char* tag,
                                   const char* operationName) {
    if (!status.isOk()) {
        jclass ex = env->FindClass("java/lang/RuntimeException");
        if (ex) {
            string what = string(operationName) + " failed: " + status.getDescription();
            env->ThrowNew(ex, what.c_str());
        }
        string logMsg = string(operationName) + " failed in " + tag;
        __android_log_write(ANDROID_LOG_ERROR, tag, logMsg.c_str());
    }
}

static void throwUnsatisfiedLinkError(JNIEnv* env, const char* msg) {
    jclass ex = env->FindClass("java/lang/UnsatisfiedLinkError");
    if (!ex) {
        env->FatalError("Unable to find java/lang/UnsatisfiedLinkError");
        return;
    }
    env->ThrowNew(ex, msg);
}

static IResponsePeer* validateIResponsePeer(JNIEnv* env, IResponsePeer* peer, const char* tag) {
  if (!peer || !peer->iface) {
    jclass ex = env->FindClass("java / lang / IllegalStateException");
    if (ex) env->ThrowNew(ex, "IResponsePeer is null or released");
    __android_log_write(ANDROID_LOG_ERROR, tag, "Failed to reinterpret_cast IResponsePeer from pointer ");
    return nullptr;
  }
  return peer;
}

static void nativeOnResponse(
        JNIEnv* env,
        [[maybe_unused]] jclass clazz,
        jlong peerLong,
        jstring jmessage,
        jint jres) {

  constexpr char TAG[] = "nativeOnResponse";

  auto* peer = reinterpret_cast<IResponsePeer*>(peerLong);
  if (!validateIResponsePeer(env, peer, TAG)) {
      return;
  }

  string message = convertJStringToString(env, jmessage);
  ScopedAStatus status = peer->iface->onResponse(message, static_cast<int32_t>(jres));

  if (!status.isOk()) {
      handleScopedAStatusError(env, status, TAG, "IResponse.onResponse");
      return;
  }
}

static void nativeOnError(
        JNIEnv* env,
        [[maybe_unused]] jclass clazz,
        jlong peerLong,
        jstring jmessage) {

  constexpr char TAG[] = "nativeOnError";

  auto* peer = reinterpret_cast<IResponsePeer*>(peerLong);
  if (!validateIResponsePeer(env, peer, TAG)) {
      return;
  }

  string message = convertJStringToString(env, jmessage);
  ScopedAStatus status = peer->iface->onError(message);

  if (!status.isOk()) {
      handleScopedAStatusError(env, status, TAG, "IResponse.onError");
      return;
  }
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
    "-Xms30m",
    "-Xmx30m",
    "-cp",
    "/mnt/apk/assets/confidential-service.dex",
    nullptr
};

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
    jclass jClassIExampleInterface;
    jmethodID jMethodIExampleInterfaceDoSomething;
    jmethodID jMethodIExampleInterfaceAddInt;
    jmethodID jMethodIExampleInterfaceGetRandomNumber;
    jmethodID jMethodIExampleInterfaceGetRandomNumberFromCallback;

    jobject jObjectIBinder;
    jobject jObjectIResponseIBinder;
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

        jclass jThrowable = env->FindClass("java/lang/Throwable");
        CHECK_NULL(jThrowable, "Unable to locate class java.lang.Throwable", EEXIST);
        jmethodID jGetExceptionMessage = env->GetMethodID(jThrowable, "getMessage", "()Ljava/lang/String;");
        CHECK_NULL(jGetExceptionMessage, "Unable to locate java.lang.Throwable::getMessage() function", EEXIST);

        string jSignatureOnBind = string("(L") + INTENT_CLASS + ";)L" + IBINDER_CLASS + ";";
        string jSignatureOnUnbind = string("(L") + INTENT_CLASS + ";)Z";

        jclass jClassExampleService = env->FindClass(EXAMPLE_SERVICE_CLASS);
        CHECK_NULL(jClassExampleService, "Unable to locate class ExampleService", EEXIST);
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
        jclass jClassIExampleInterface = env->FindClass(IEXAMPLE_INTERFACE_CLASS);
        CHECK_NULL(jClassIExampleInterface, "Unable to locate class IExampleInterface.Stub", EEXIST);
        jmethodID jMethodIExampleInterfaceDoSomething =
            env->GetMethodID(jClassIExampleInterface, "doSomething", "()V");
        CHECK_NULL(jMethodIExampleInterfaceDoSomething, "Unable to locate method doSomething", EEXIST);
        jmethodID jMethodIExampleInterfaceAddInt =
            env->GetMethodID(jClassIExampleInterface, "addInt", "(II)I");
        CHECK_NULL(jMethodIExampleInterfaceAddInt, "Unable to locate method addInt", EEXIST);
        jmethodID jMethodIExampleInterfaceGetRandomNumber =
            env->GetMethodID(jClassIExampleInterface, "getRandomNumber", "()I");
        CHECK_NULL(jMethodIExampleInterfaceGetRandomNumber, "Unable to locate method getRandomNumber", EEXIST);
        jmethodID jMethodIExampleInterfaceGetRandomNumberFromCallback =
            env->GetMethodID(jClassIExampleInterface, "getRandomNumberFromCallback", "(Lcom/examplecc/service/IResponse;)V");
        CHECK_NULL(jMethodIExampleInterfaceGetRandomNumberFromCallback, "Unable to locate method getRandomNumberFromCallback", EEXIST);

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

            jClassIExampleInterface,
            jMethodIExampleInterfaceDoSomething,
            jMethodIExampleInterfaceAddInt,
            jMethodIExampleInterfaceGetRandomNumber,
            jMethodIExampleInterfaceGetRandomNumberFromCallback,

            nullptr   // object instance, will be filled in the lifecycle calls
        );

        return *ctx;
    }
};

class JniRealmService : public BnRealmService
{
    std::unique_ptr<JvmInstance> gJvmInstance;

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

static void ensureRegisterIResponseProxyNatives(JNIEnv* env, jclass proxyCls) {
  constexpr char TAG[] = "IResponseProxyNatives";
  static bool done = false;
  if (done) return;

  if (proxyCls == nullptr) {
      __android_log_write(ANDROID_LOG_ERROR, TAG, "RegisterNatives: IResponseProxy class is null");
      throwUnsatisfiedLinkError(env, "RegisterNatives: IResponseProxy class is null");
      return;
  }

  static const JNINativeMethod kMethods[] = {
    { "jniOnResponse", "(JLjava/lang/String;I)V", (void*)nativeOnResponse },
    { "jniOnError", "(JLjava/lang/String;)V", (void*)nativeOnError },
  };
  const int kNumMethods = static_cast<int>(sizeof(kMethods) / sizeof(kMethods[0]));

  const jint rc = env->RegisterNatives(proxyCls, kMethods, kNumMethods);
  if (rc != 0) {
      __android_log_write(ANDROID_LOG_ERROR, TAG, "RegisterNatives failed for com.islet.binder.service.IResponseProxy");
      throwUnsatisfiedLinkError(env, "RegisterNatives failed for com.islet.binder.service.IResponseProxy");
      return;
  }

  done = true;
}

void callGetRandomNumberFromCallback(const std::shared_ptr<IResponse>& response, const LocalJniContext &ctx) {
  JNIEnv *env = ctx.env;

  auto *peer = new IResponsePeer{.iface = std::move(response)};
  CHECK_NULL_JNI_RETURN_VOID(peer, "Unable to create IResponsePeer", EEXIST);

  jlong nativePeer = reinterpret_cast<jlong>(peer);
  if (!nativePeer) {
  __android_log_write(ANDROID_LOG_ERROR, TAG, "Failed to reinterpret_cast nativePeer");
  return;
  }

  jclass clsProxy = env->FindClass("com/islet/binder/service/IResponseProxy");
  CHECK_NULL_JNI_RETURN_VOID(clsProxy, "Unable to locate class IResponseProxy", EEXIST);

  ensureRegisterIResponseProxyNatives(env, clsProxy);

  jmethodID ctor = env->GetMethodID(clsProxy, "<init>", "(J)V");
  CHECK_NULL_JNI_RETURN_VOID(ctor, "Unable to locate IResponseProxy ctor", EEXIST);
  jobject proxy = env->NewObject(clsProxy, ctor, nativePeer);
  CHECK_NULL_JNI_RETURN_VOID(proxy, "Unable to instantiate IResponseProxy", EEXIST);

  env->CallVoidMethod(ctx.jObjectIBinder, ctx.jMethodIExampleInterfaceGetRandomNumberFromCallback, proxy);
}

public: // AIDL Methods start
  ScopedAStatus doSomething() override {
    __android_log_write(ANDROID_LOG_INFO, TAG, "Start doSomething;");
    return perform_JNI([](const LocalJniContext &ctx) {
        ctx.env->CallVoidMethod(ctx.jObjectIBinder, ctx.jMethodIExampleInterfaceDoSomething);
    });
  }
  ScopedAStatus addInt(int32_t a, int32_t b, int32_t* out) override {
    __android_log_write(ANDROID_LOG_INFO, TAG, "Start addInt;");
    return perform_JNI<jint>(out, [a, b](const LocalJniContext &ctx) {
        return ctx.env->CallIntMethod(ctx.jObjectIBinder, ctx.jMethodIExampleInterfaceAddInt, a, b);
    });
  }
  ScopedAStatus getRandomNumber(int32_t* out) override {
    __android_log_write(ANDROID_LOG_INFO, TAG, "Start getRandomNumber;");
    return perform_JNI<jint>(out, [](const LocalJniContext &ctx) {
        return ctx.env->CallIntMethod(ctx.jObjectIBinder, ctx.jMethodIExampleInterfaceGetRandomNumber);
    });
  }
  ScopedAStatus getRandomNumberFromCallback(const std::shared_ptr<IResponse>& response) override {
    __android_log_write(ANDROID_LOG_INFO, TAG, "Start getRandomNumberFromCallback;");
    return perform_JNI([response, this](const LocalJniContext &ctx) {
    this->callGetRandomNumberFromCallback(response, ctx);
    });
  }

  // it won't actually be called on create, but on connection
  ScopedAStatus onCreate() override {
      __android_log_write(ANDROID_LOG_INFO, TAG, "onCreate();");
      auto jvm_result = JvmInstance::init(jvm_argv);

      if (!jvm_result.has_value())
          return from_result(jvm_result);
      gJvmInstance = std::move(jvm_result.value());

      return perform_JNI([](LocalJniContext &ctx) {
              jobject jObjectExampleService = ctx.env->NewObject(ctx.jClassExampleService, ctx.jMethodExampleServiceCtor);
              CHECK_NULL_JNI(jObjectExampleService, "Unable to instantiate ExampleService");

              ctx.env->CallVoidMethod(jObjectExampleService, ctx.jMethodExampleServiceOnCreate);
              CHECK_EXCEPTION_JNI("Unable to call onCreate");

              ctx.jObjectExampleService = jObjectExampleService;
      });
  }


  // it won't actually be called on bind, but on connection
  ScopedAStatus onBind(::ndk::SpAIBinder* out) override {
      __android_log_write(ANDROID_LOG_INFO, TAG, "onBind();");

      AIBinder* binder = nullptr;

      auto result = gJvmInstance->localContext();

      if (!result.has_value())
          return from_result(result);

      auto &ctx = *result.value();

      jobject jObjectIntent = ctx.env->NewObject(ctx.jClassIntent, ctx.jMethodIntentCtor);
      if (jObjectIntent == nullptr || ctx.env->ExceptionCheck()) {
          __android_log_write(ANDROID_LOG_ERROR, TAG, "Cannot instantiate Intent");
          ctx.env->ExceptionDescribe();
              return ScopedAStatus::fromServiceSpecificErrorWithMessage(
                  1,
                  "Cannot instantiate Intent"
          );
      }

      jobject jObjectIBinder = ctx.env->CallObjectMethod(ctx.jObjectExampleService, ctx.jMethodExampleServiceOnBind, jObjectIntent);
      if (jObjectIBinder == nullptr || ctx.env->ExceptionCheck()) {
          __android_log_write(ANDROID_LOG_ERROR, TAG, "Cannot call onBind");
          ctx.env->ExceptionDescribe();
              return ScopedAStatus::fromServiceSpecificErrorWithMessage(
                  1,
                  "Cannot call onBind"
          );
      }


      ctx.jObjectIntent = jObjectIntent;
      ctx.jObjectIBinder = jObjectIBinder;

      AIBinder_setupRuntimeBindings(nullptr, android::getibinderForJavaObjectPtr(), nullptr, nullptr);

      AIBinder *nativeBinder = AIBinder_fromJavaBinder(ctx.env, jObjectIBinder);


       __android_log_print(ANDROID_LOG_ERROR, TAG, "onBind() returned Java Binder env = %p nativeBinder = %p javaBinder = %p\n", ctx.env, nativeBinder, jObjectIBinder);

      auto status = check_exception(ctx);

      out->set(nativeBinder);

      return status;
  }

  ScopedAStatus onUnbind() override {
      __android_log_write(ANDROID_LOG_INFO, TAG, "onUnbind();");
      return perform_JNI([](const LocalJniContext &ctx) {
              jboolean ignored = ctx.env->CallBooleanMethod(ctx.jObjectExampleService, ctx.jMethodExampleServiceOnUnbind, ctx.jObjectIntent);
              CHECK_EXCEPTION_JNI("Unable to call onUnbind");
      });
  }

  ScopedAStatus onDestroy() override {
      __android_log_write(ANDROID_LOG_INFO, TAG, "onDestroy();");
      return perform_JNI([](const LocalJniContext &ctx) {
              ctx.env->CallVoidMethod(ctx.jObjectExampleService, ctx.jMethodExampleServiceOnDestroy);
              CHECK_EXCEPTION_JNI("Unable to call onDestroy");
      });
  }
}; // JniRealmService class

Result<void> start_service()
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

    auto service = ndk::SharedRefBase::make<JniRealmService>();

    auto callback = []([[maybe_unused]] void* param) { AVmPayload_notifyPayloadReady(); };
    AVmPayload_runVsockRpcServer(service->asBinder().get(), service->PORT, callback,
                                 nullptr);

    return {};
}
} // Anonymous namespace

extern "C" int AVmPayload_main()
{
    __android_log_write(ANDROID_LOG_INFO, TAG, "Hello from AVmPayload_main");
    __system_property_set("debug.microdroid.app.run", "true");

    static JniInvocation jni_invocation;
    if (!jni_invocation.Init(nullptr)) {
        __android_log_write(ANDROID_LOG_ERROR, TAG, "Failed to initialize JNI invocation API");
        return 1;
    }

    auto res = start_service();

    if (res.ok()) {
        return 0;
    } else {
        __android_log_write(ANDROID_LOG_ERROR, TAG, res.error().message().c_str());
        return 1;
    }
}
