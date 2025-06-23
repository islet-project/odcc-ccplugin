// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

package com.islet.binder.service;
interface IRealmService {
    const long PORT = 5678;

    /* additional Microdroid lifetime related methods */
    IBinder onBindForTargetService();
}
