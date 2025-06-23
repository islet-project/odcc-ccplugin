/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk -I vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja --rpc -h external/CCPlugIn/gen -o external/CCPlugIn/gen -N . -N external/CCPlugIn/gen/ external/CCPlugIn/gen/com/islet/binder/service/IRealmService.aidl
 */
#pragma once

#include "aidl/com/islet/binder/service/IRealmService.h"

#include <android/binder_ibinder.h>
#include <cassert>

#ifndef __BIONIC__
#ifndef __assert2
#define __assert2(a,b,c,d) ((void)0)
#endif
#endif

namespace aidl {
namespace com {
namespace islet {
namespace binder {
namespace service {
class BnRealmService : public ::ndk::BnCInterface<IRealmService> {
public:
  BnRealmService();
  virtual ~BnRealmService();
protected:
  ::ndk::SpAIBinder createBinder() override;
private:
};
class IRealmServiceDelegator : public BnRealmService {
public:
  explicit IRealmServiceDelegator(const std::shared_ptr<IRealmService> &impl) : _impl(impl) {
  }

  ::ndk::ScopedAStatus doSomething() override {
    return _impl->doSomething();
  }
  ::ndk::ScopedAStatus addInt(int32_t in_a, int32_t in_b, int32_t* _aidl_return) override {
    return _impl->addInt(in_a, in_b, _aidl_return);
  }
  ::ndk::ScopedAStatus getRandomNumber(int32_t* _aidl_return) override {
    return _impl->getRandomNumber(_aidl_return);
  }
  ::ndk::ScopedAStatus getRandomNumberFromCallback(const std::shared_ptr<::aidl::com::examplecc::service::IResponse>& in_response) override {
    return _impl->getRandomNumberFromCallback(in_response);
  }
  ::ndk::ScopedAStatus onCreate() override {
    return _impl->onCreate();
  }
  ::ndk::ScopedAStatus onBind(::ndk::SpAIBinder* _aidl_return) override {
    return _impl->onBind(_aidl_return);
  }
  ::ndk::ScopedAStatus onUnbind() override {
    return _impl->onUnbind();
  }
  ::ndk::ScopedAStatus onDestroy() override {
    return _impl->onDestroy();
  }
protected:
private:
  std::shared_ptr<IRealmService> _impl;
};

}  // namespace service
}  // namespace binder
}  // namespace islet
}  // namespace com
}  // namespace aidl
