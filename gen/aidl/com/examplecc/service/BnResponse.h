/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/ vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IResponse.aidl
 */
#pragma once

#include "aidl/com/examplecc/service/IResponse.h"

#include <android/binder_ibinder.h>
#include <cassert>

#ifndef __BIONIC__
#ifndef __assert2
#define __assert2(a,b,c,d) ((void)0)
#endif
#endif

namespace aidl {
namespace com {
namespace examplecc {
namespace service {
class BnResponse : public ::ndk::BnCInterface<IResponse> {
public:
  BnResponse();
  virtual ~BnResponse();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IResponseDelegator : public BnResponse {
public:
  explicit IResponseDelegator(const std::shared_ptr<IResponse> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus onResponse(const std::string& in_message, int32_t in_res) override {
    return _impl->onResponse(in_message, in_res);
  }
  ::ndk::ScopedAStatus onError(const std::string& in_message) override {
    return _impl->onError(in_message);
  }
protected:
private:
  std::shared_ptr<IResponse> _impl;
};

}  // namespace service
}  // namespace examplecc
}  // namespace com
}  // namespace aidl
