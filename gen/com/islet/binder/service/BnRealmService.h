/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/gen/ external/CCPlugIn/gen/com/islet/binder/service/IRealmService.aidl
 */
#pragma once

#include <binder/IInterface.h>
#include <com/islet/binder/service/IRealmService.h>
#include <binder/Delegate.h>
#include <com/examplecc/service/BnResponse.h>
#include <com/islet/binder/service/BnRealmService.h>


namespace com {
namespace islet {
namespace binder {
namespace service {
class LIBBINDER_EXPORTED BnRealmService : public ::android::BnInterface<IRealmService> {
public:
  static constexpr uint32_t TRANSACTION_doSomething = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_addInt = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getRandomNumber = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getRandomNumberFromCallback = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onCreate = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_onBind = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_onUnbind = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_onDestroy = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  explicit BnRealmService();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnRealmService

class LIBBINDER_EXPORTED IRealmServiceDelegator : public BnRealmService {
public:
  explicit IRealmServiceDelegator(const ::android::sp<IRealmService> &impl) : _aidl_delegate(impl) {}

  ::android::sp<IRealmService> getImpl() { return _aidl_delegate; }
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
  ::android::binder::Status onCreate() override {
    return _aidl_delegate->onCreate();
  }
  ::android::binder::Status onBind(::android::sp<::android::IBinder>* _aidl_return) override {
    return _aidl_delegate->onBind(_aidl_return);
  }
  ::android::binder::Status onUnbind() override {
    return _aidl_delegate->onUnbind();
  }
  ::android::binder::Status onDestroy() override {
    return _aidl_delegate->onDestroy();
  }
private:
  ::android::sp<IRealmService> _aidl_delegate;
};  // class IRealmServiceDelegator
}  // namespace service
}  // namespace binder
}  // namespace islet
}  // namespace com
