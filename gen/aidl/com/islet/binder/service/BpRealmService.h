/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/gen/ external/CCPlugIn/gen/com/islet/binder/service/IRealmService.aidl
 */
#pragma once

#include "aidl/com/islet/binder/service/IRealmService.h"

#include <android/binder_ibinder.h>

namespace aidl {
namespace com {
namespace islet {
namespace binder {
namespace service {
class BpRealmService : public ::ndk::BpCInterface<IRealmService> {
public:
  explicit BpRealmService(const ::ndk::SpAIBinder& binder);
  virtual ~BpRealmService();

  ::ndk::ScopedAStatus doSomething() override;
  ::ndk::ScopedAStatus addInt(int32_t in_a, int32_t in_b, int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus getRandomNumber(int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus getRandomNumberFromCallback(const std::shared_ptr<::aidl::com::examplecc::service::IResponse>& in_response) override;
  ::ndk::ScopedAStatus onCreate() override;
  ::ndk::ScopedAStatus onBind(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus onUnbind() override;
  ::ndk::ScopedAStatus onDestroy() override;
};
}  // namespace service
}  // namespace binder
}  // namespace islet
}  // namespace com
}  // namespace aidl
