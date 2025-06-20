/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

 #ifndef BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_FETCH_MANAGER_H_
 #define BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_FETCH_MANAGER_H_

 #define Fetch \
 Fetch_ChromiumImpl(ScriptState*, \
    FetchRequestData*, \
    AbortSignal*, \
    ExceptionState&); \
 ScriptPromise<Response> Fetch

 #include "src/third_party/blink/renderer/core/fetch/fetch_manager.h" 
 #undef Fetch

 #endif  // BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_FETCH_MANAGER_H_