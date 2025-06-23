/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=java -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja -o external/CCPlugIn/gen -N . -N vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IExampleInterface.aidl
 */
  
/*
 * Copyright 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.islet.binder.service;
interface IRealmService {
    const long PORT = 5678;
    void doSomething();
    int addInt(int a, int b);
    int getRandomNumber();
    void getRandomNumberFromCallback(com.examplecc.service.IResponse response);
  

    /* additional Microdroid lifetime related methods */
    void onCreate();
    IBinder onBind();
    void onUnbind();
    void onDestroy();
}