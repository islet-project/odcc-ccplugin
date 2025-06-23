// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <aidl/com/islet/binder/service/BnRealmService.h>
#include <android/binder_interface_utils.h>

using aidl::com::islet::binder::service::BnRealmService;
using ndk::ScopedAStatus;

class RealmServiceImpl : public BnRealmService
{
private:
    static constexpr char TAG[] = "RealmServiceImpl";

public:
    RealmServiceImpl() = default;
    virtual ~RealmServiceImpl() = default;

    ScopedAStatus onBindForTargetService(::ndk::SpAIBinder* out) override {
        __android_log_write(ANDROID_LOG_INFO, TAG, "onBindForTargetService() called");

        NativeCCStub::onCreate();
        __android_log_write(ANDROID_LOG_INFO, TAG, "NativeCCStub::onCreate() called");

        return NativeCCStub::onBind(out);
    }
};
