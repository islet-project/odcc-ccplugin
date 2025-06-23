/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/ vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IResponse.aidl
 */
#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <android/binder_interface_utils.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace com {
namespace examplecc {
namespace service {
class IResponseDelegator;

class IResponse : public ::ndk::ICInterface {
public:
  typedef IResponseDelegator DefaultDelegator;
  static const char* descriptor;
  IResponse();
  virtual ~IResponse();

  static constexpr uint32_t TRANSACTION_onResponse = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onError = FIRST_CALL_TRANSACTION + 1;

  static std::shared_ptr<IResponse> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IResponse>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IResponse>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IResponse>& impl);
  static const std::shared_ptr<IResponse>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onResponse(const std::string& in_message, int32_t in_res) = 0;
  virtual ::ndk::ScopedAStatus onError(const std::string& in_message) = 0;
private:
  static std::shared_ptr<IResponse> default_impl;
};
class IResponseDefault : public IResponse {
public:
  ::ndk::ScopedAStatus onResponse(const std::string& in_message, int32_t in_res) override;
  ::ndk::ScopedAStatus onError(const std::string& in_message) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace service
}  // namespace examplecc
}  // namespace com
}  // namespace aidl
