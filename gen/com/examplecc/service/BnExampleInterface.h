/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IExampleInterface.aidl
 */
#pragma once

#include <binder/IInterface.h>
#include <com/examplecc/service/IExampleInterface.h>
#include <binder/Delegate.h>
#include <com/examplecc/service/BnExampleInterface.h>
#include <com/examplecc/service/BnResponse.h>


namespace com {
namespace examplecc {
namespace service {
class LIBBINDER_EXPORTED BnExampleInterface : public ::android::BnInterface<IExampleInterface> {
public:
  static constexpr uint32_t TRANSACTION_doSomething = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_addInt = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getRandomNumber = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getRandomNumberFromCallback = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  explicit BnExampleInterface();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnExampleInterface

class LIBBINDER_EXPORTED IExampleInterfaceDelegator : public BnExampleInterface {
public:
  explicit IExampleInterfaceDelegator(const ::android::sp<IExampleInterface> &impl) : _aidl_delegate(impl) {}

  ::android::sp<IExampleInterface> getImpl() { return _aidl_delegate; }
  ::android::binder::Status doSomething() override {
    return _aidl_delegate->doSomething();
  }
  ::android::binder::Status addInt(int32_t a, int32_t b, int32_t* _aidl_return) override {
    return _aidl_delegate->addInt(a, b, _aidl_return);
  }
  ::android::binder::Status getRandomNumber(int32_t* _aidl_return) override {
    return _aidl_delegate->getRandomNumber(_aidl_return);
  }
  ::android::binder::Status getRandomNumberFromCallback(const ::android::sp<::com::examplecc::service::IResponse>& response) override {
    ::android::sp<::com::examplecc::service::IResponseDelegator> _response;
    if (response) {
      _response = ::android::sp<::com::examplecc::service::IResponseDelegator>::cast(delegate(response));
    }
    return _aidl_delegate->getRandomNumberFromCallback(_response);
  }
private:
  ::android::sp<IExampleInterface> _aidl_delegate;
};  // class IExampleInterfaceDelegator
}  // namespace service
}  // namespace examplecc
}  // namespace com
