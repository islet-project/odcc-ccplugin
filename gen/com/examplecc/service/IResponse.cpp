/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/ vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IResponse.aidl
 */
#include "aidl/com/examplecc/service/IResponse.h"

#include <android/binder_parcel_utils.h>
#include <aidl/com/examplecc/service/BnResponse.h>
#include <aidl/com/examplecc/service/BpResponse.h>

namespace aidl {
namespace com {
namespace examplecc {
namespace service {
static binder_status_t _aidl_com_examplecc_service_IResponse_onTransact(AIBinder* _aidl_binder, transaction_code_t _aidl_code, const AParcel* _aidl_in, AParcel* _aidl_out) {
  (void)_aidl_in;
  (void)_aidl_out;
  binder_status_t _aidl_ret_status = STATUS_UNKNOWN_TRANSACTION;
  std::shared_ptr<BnResponse> _aidl_impl = std::static_pointer_cast<BnResponse>(::ndk::ICInterface::asInterface(_aidl_binder));
  switch (_aidl_code) {
    case (FIRST_CALL_TRANSACTION + 0 /*onResponse*/): {
      std::string in_message;
      int32_t in_res;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_message);
      if (_aidl_ret_status != STATUS_OK) break;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_res);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onResponse(in_message, in_res);
      _aidl_ret_status = AParcel_writeStatusHeader(_aidl_out, _aidl_status.get());
      if (_aidl_ret_status != STATUS_OK) break;

      if (!AStatus_isOk(_aidl_status.get())) break;

      break;
    }
    case (FIRST_CALL_TRANSACTION + 1 /*onError*/): {
      std::string in_message;

      _aidl_ret_status = ::ndk::AParcel_readData(_aidl_in, &in_message);
      if (_aidl_ret_status != STATUS_OK) break;

      ::ndk::ScopedAStatus _aidl_status = _aidl_impl->onError(in_message);
      _aidl_ret_status = STATUS_OK;
      break;
    }
  }
  return _aidl_ret_status;
}

static AIBinder_Class* _g_aidl_com_examplecc_service_IResponse_clazz = ::ndk::ICInterface::defineClass(IResponse::descriptor, _aidl_com_examplecc_service_IResponse_onTransact);

BpResponse::BpResponse(const ::ndk::SpAIBinder& binder) : BpCInterface(binder) {}
BpResponse::~BpResponse() {}

::ndk::ScopedAStatus BpResponse::onResponse(const std::string& in_message, int32_t in_res) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_message);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_res);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 0 /*onResponse*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    0
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IResponse::getDefaultImpl()) {
    _aidl_status = IResponse::getDefaultImpl()->onResponse(in_message, in_res);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AParcel_readStatusHeader(_aidl_out.get(), _aidl_status.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  if (!AStatus_isOk(_aidl_status.get())) goto _aidl_status_return;
  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
::ndk::ScopedAStatus BpResponse::onError(const std::string& in_message) {
  binder_status_t _aidl_ret_status = STATUS_OK;
  ::ndk::ScopedAStatus _aidl_status;
  ::ndk::ScopedAParcel _aidl_in;
  ::ndk::ScopedAParcel _aidl_out;

  _aidl_ret_status = AIBinder_prepareTransaction(asBinderReference().get(), _aidl_in.getR());
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = ::ndk::AParcel_writeData(_aidl_in.get(), in_message);
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_ret_status = AIBinder_transact(
    asBinderReference().get(),
    (FIRST_CALL_TRANSACTION + 1 /*onError*/),
    _aidl_in.getR(),
    _aidl_out.getR(),
    FLAG_ONEWAY
    #ifdef BINDER_STABILITY_SUPPORT
    | static_cast<int>(FLAG_PRIVATE_LOCAL)
    #endif  // BINDER_STABILITY_SUPPORT
    );
  if (_aidl_ret_status == STATUS_UNKNOWN_TRANSACTION && IResponse::getDefaultImpl()) {
    _aidl_status = IResponse::getDefaultImpl()->onError(in_message);
    goto _aidl_status_return;
  }
  if (_aidl_ret_status != STATUS_OK) goto _aidl_error;

  _aidl_error:
  _aidl_status.set(AStatus_fromStatus(_aidl_ret_status));
  _aidl_status_return:
  return _aidl_status;
}
// Source for BnResponse
BnResponse::BnResponse() {}
BnResponse::~BnResponse() {}
::ndk::SpAIBinder BnResponse::createBinder() {
  AIBinder* binder = AIBinder_new(_g_aidl_com_examplecc_service_IResponse_clazz, static_cast<void*>(this));
  #ifdef BINDER_STABILITY_SUPPORT
  AIBinder_markCompilationUnitStability(binder);
  #endif  // BINDER_STABILITY_SUPPORT
  return ::ndk::SpAIBinder(binder);
}
// Source for IResponse
const char* IResponse::descriptor = "com.examplecc.service.IResponse";
IResponse::IResponse() {}
IResponse::~IResponse() {}


std::shared_ptr<IResponse> IResponse::fromBinder(const ::ndk::SpAIBinder& binder) {
  if (!AIBinder_associateClass(binder.get(), _g_aidl_com_examplecc_service_IResponse_clazz)) {
    #if __ANDROID_API__ >= 31
    const AIBinder_Class* originalClass = AIBinder_getClass(binder.get());
    if (originalClass == nullptr) return nullptr;
    if (0 == strcmp(AIBinder_Class_getDescriptor(originalClass), descriptor)) {
      return ::ndk::SharedRefBase::make<BpResponse>(binder);
    }
    #endif
    return nullptr;
  }
  std::shared_ptr<::ndk::ICInterface> interface = ::ndk::ICInterface::asInterface(binder.get());
  if (interface) {
    return std::static_pointer_cast<IResponse>(interface);
  }
  return ::ndk::SharedRefBase::make<BpResponse>(binder);
}

binder_status_t IResponse::writeToParcel(AParcel* parcel, const std::shared_ptr<IResponse>& instance) {
  return AParcel_writeStrongBinder(parcel, instance ? instance->asBinder().get() : nullptr);
}
binder_status_t IResponse::readFromParcel(const AParcel* parcel, std::shared_ptr<IResponse>* instance) {
  ::ndk::SpAIBinder binder;
  binder_status_t status = AParcel_readStrongBinder(parcel, binder.getR());
  if (status != STATUS_OK) return status;
  *instance = IResponse::fromBinder(binder);
  return STATUS_OK;
}
bool IResponse::setDefaultImpl(const std::shared_ptr<IResponse>& impl) {
  // Only one user of this interface can use this function
  // at a time. This is a heuristic to detect if two different
  // users in the same process use this function.
  assert(!IResponse::default_impl);
  if (impl) {
    IResponse::default_impl = impl;
    return true;
  }
  return false;
}
const std::shared_ptr<IResponse>& IResponse::getDefaultImpl() {
  return IResponse::default_impl;
}
std::shared_ptr<IResponse> IResponse::default_impl = nullptr;
::ndk::ScopedAStatus IResponseDefault::onResponse(const std::string& /*in_message*/, int32_t /*in_res*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::ScopedAStatus IResponseDefault::onError(const std::string& /*in_message*/) {
  ::ndk::ScopedAStatus _aidl_status;
  _aidl_status.set(AStatus_fromStatus(STATUS_UNKNOWN_TRANSACTION));
  return _aidl_status;
}
::ndk::SpAIBinder IResponseDefault::asBinder() {
  return ::ndk::SpAIBinder();
}
bool IResponseDefault::isRemote() {
  return false;
}
}  // namespace service
}  // namespace examplecc
}  // namespace com
}  // namespace aidl
