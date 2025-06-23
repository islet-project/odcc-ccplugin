// Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <sys/cdefs.h>

#include <jni.h>

__BEGIN_DECLS

/**
 * Registers JNI bindings for com.islet.Cca class.
 *
 * \return returns JNI_OK if the call was successful.
 * In case of failure it returns an error code defined in jni.h header
 */
int register_com_islet_Cca(JNIEnv* env);

__END_DECLS
