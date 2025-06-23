/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/gen/ external/CCPlugIn/gen/com/islet/binder/service/IRealmService.aidl
 */
#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/islet/binder/service/IRealmService.h>

namespace com {
namespace islet {
namespace binder {
namespace service {
class LIBBINDER_EXPORTED BpRealmService : public ::android::BpInterface<IRealmService> {
public:
  explicit BpRealmService(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpRealmService() = default;
  ::android::binder::Status doSomething() override;
  ::android::binder::Status addInt(int32_t a, int32_t b, int32_t* _aidl_return) override;
  ::android::binder::Status getRandomNumber(int32_t* _aidl_return) override;
  ::android::binder::Status getRandomNumberFromCallback(const ::android::sp<::com::examplecc::service::IResponse>& response) override;
  ::android::binder::Status onCreate() override;
  ::android::binder::Status onBind(::android::sp<::android::IBinder>* _aidl_return) override;
  ::android::binder::Status onUnbind() override;
  ::android::binder::Status onDestroy() override;
};  // class BpRealmService
}  // namespace service
}  // namespace binder
}  // namespace islet
}  // namespace com
