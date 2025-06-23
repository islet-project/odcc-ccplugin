/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/ vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IResponse.aidl
 */
#pragma once

#include "aidl/com/examplecc/service/IResponse.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace examplecc {
namespace service {
class BpResponse : public ::ndk::BpCInterface<IResponse> {
public:
  explicit BpResponse(const ::ndk::SpAIBinder& binder);
  virtual ~BpResponse();

  ::ndk::ScopedAStatus onResponse(const std::string& in_message, int32_t in_res) override;
  ::ndk::ScopedAStatus onError(const std::string& in_message) override;
};
}  // namespace service
}  // namespace examplecc
}  // namespace com
}  // namespace aidl
