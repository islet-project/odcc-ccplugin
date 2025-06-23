/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=cpp -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/gen/ external/CCPlugIn/gen/com/islet/binder/service/IRealmService.aidl
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
namespace islet {
namespace binder {
namespace service {
class LIBBINDER_EXPORTED IRealmServiceDelegator;

class LIBBINDER_EXPORTED IRealmService : public ::android::IInterface {
public:
  typedef IRealmServiceDelegator DefaultDelegator;
  DECLARE_META_INTERFACE(RealmService)
  enum : int64_t { PORT = 5678L };
  virtual ::android::binder::Status doSomething() = 0;
  virtual ::android::binder::Status addInt(int32_t a, int32_t b, int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status getRandomNumber(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status getRandomNumberFromCallback(const ::android::sp<::com::examplecc::service::IResponse>& response) = 0;
  virtual ::android::binder::Status onCreate() = 0;
  virtual ::android::binder::Status onBind(::android::sp<::android::IBinder>* _aidl_return) = 0;
  virtual ::android::binder::Status onUnbind() = 0;
  virtual ::android::binder::Status onDestroy() = 0;
};  // class IRealmService

class LIBBINDER_EXPORTED IRealmServiceDefault : public IRealmService {
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
  ::android::binder::Status onCreate() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onBind(::android::sp<::android::IBinder>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onUnbind() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onDestroy() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
};  // class IRealmServiceDefault
}  // namespace service
}  // namespace binder
}  // namespace islet
}  // namespace com
