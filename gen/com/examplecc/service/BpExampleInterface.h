/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IExampleInterface.aidl
 */
#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/examplecc/service/IExampleInterface.h>

namespace com {
namespace examplecc {
namespace service {
class LIBBINDER_EXPORTED BpExampleInterface : public ::android::BpInterface<IExampleInterface> {
public:
  explicit BpExampleInterface(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpExampleInterface() = default;
  ::android::binder::Status doSomething() override;
  ::android::binder::Status addInt(int32_t a, int32_t b, int32_t* _aidl_return) override;
  ::android::binder::Status getRandomNumber(int32_t* _aidl_return) override;
  ::android::binder::Status getRandomNumberFromCallback(const ::android::sp<::com::examplecc::service::IResponse>& response) override;
};  // class BpExampleInterface
}  // namespace service
}  // namespace examplecc
}  // namespace com
