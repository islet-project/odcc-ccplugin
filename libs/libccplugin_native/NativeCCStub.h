// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <binder/Status.h>
#include <jni.h>
#include <android/binder_interface_utils.h>

namespace NativeCCStub {

using ndk::ScopedAStatus;

struct LocalJniContext;

class JvmInstance;

extern std::unique_ptr<JvmInstance> gJvmInstance;

ScopedAStatus check_exception(const LocalJniContext &ctx);

template<typename Ret>
ScopedAStatus perform_JNI(Ret *out, std::function<Ret(LocalJniContext &)> f);

ScopedAStatus perform_JNI(std::function<void(LocalJniContext &)> f);

// Service lifecycle function declarations
ScopedAStatus onCreate();

ScopedAStatus onBind(::ndk::SpAIBinder* out);

ScopedAStatus onUnbind();

ScopedAStatus onDestroy();

} // namespace NativeCCStub

// External C function to get JavaVM from JvmInstance
extern "C" JavaVM* AndroidRuntimeGetJavaVM();
