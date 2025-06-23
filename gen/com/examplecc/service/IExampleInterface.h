/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IExampleInterface.aidl
 */
#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/examplecc/service/IResponse.h>
#include <cstdint>
#include <utils/StrongPointer.h>

namespace com::examplecc::service {
class IResponse;
}  // namespace com::examplecc::service
namespace com {
namespace examplecc {
namespace service {
class LIBBINDER_EXPORTED IExampleInterfaceDelegator;

class LIBBINDER_EXPORTED IExampleInterface : public ::android::IInterface {
public:
  typedef IExampleInterfaceDelegator DefaultDelegator;
  DECLARE_META_INTERFACE(ExampleInterface)
  virtual ::android::binder::Status doSomething() = 0;
  virtual ::android::binder::Status addInt(int32_t a, int32_t b, int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status getRandomNumber(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status getRandomNumberFromCallback(const ::android::sp<::com::examplecc::service::IResponse>& response) = 0;
};  // class IExampleInterface

class LIBBINDER_EXPORTED IExampleInterfaceDefault : public IExampleInterface {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status doSomething() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status addInt(int32_t /*a*/, int32_t /*b*/, int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getRandomNumber(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getRandomNumberFromCallback(const ::android::sp<::com::examplecc::service::IResponse>& /*response*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
};  // class IExampleInterfaceDefault
}  // namespace service
}  // namespace examplecc
}  // namespace com
