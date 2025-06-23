/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/gen/ external/CCPlugIn/gen/com/islet/binder/service/IRealmService.aidl
 */
#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/binder_interface_utils.h>
#include <aidl/com/examplecc/service/IResponse.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::com::examplecc::service {
class IResponse;
}  // namespace aidl::com::examplecc::service
namespace aidl {
namespace com {
namespace islet {
namespace binder {
namespace service {
class IRealmServiceDelegator;

class IRealmService : public ::ndk::ICInterface {
public:
  typedef IRealmServiceDelegator DefaultDelegator;
  static const char* descriptor;
  IRealmService();
  virtual ~IRealmService();

  enum : int64_t { PORT = 5678L };
  static constexpr uint32_t TRANSACTION_doSomething = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_addInt = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getRandomNumber = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getRandomNumberFromCallback = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onCreate = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_onBind = FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_onUnbind = FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_onDestroy = FIRST_CALL_TRANSACTION + 7;

  static std::shared_ptr<IRealmService> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IRealmService>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IRealmService>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IRealmService>& impl);
  static const std::shared_ptr<IRealmService>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus doSomething() = 0;
  virtual ::ndk::ScopedAStatus addInt(int32_t in_a, int32_t in_b, int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getRandomNumber(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getRandomNumberFromCallback(const std::shared_ptr<::aidl::com::examplecc::service::IResponse>& in_response) = 0;
  virtual ::ndk::ScopedAStatus onCreate() = 0;
  virtual ::ndk::ScopedAStatus onBind(::ndk::SpAIBinder* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus onUnbind() = 0;
  virtual ::ndk::ScopedAStatus onDestroy() = 0;
private:
  static std::shared_ptr<IRealmService> default_impl;
};
class IRealmServiceDefault : public IRealmService {
public:
  ::ndk::ScopedAStatus doSomething() override;
  ::ndk::ScopedAStatus addInt(int32_t in_a, int32_t in_b, int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus getRandomNumber(int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus getRandomNumberFromCallback(const std::shared_ptr<::aidl::com::examplecc::service::IResponse>& in_response) override;
  ::ndk::ScopedAStatus onCreate() override;
  ::ndk::ScopedAStatus onBind(::ndk::SpAIBinder* _aidl_return) override;
  ::ndk::ScopedAStatus onUnbind() override;
  ::ndk::ScopedAStatus onDestroy() override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace service
}  // namespace binder
}  // namespace islet
}  // namespace com
}  // namespace aidl
