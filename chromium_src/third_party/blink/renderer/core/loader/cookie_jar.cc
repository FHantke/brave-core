/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/core/loader/cookie_jar.h"

#include "mojo/public/cpp/base/shared_memory_version.h"

#include "third_party/blink/renderer/core/frame/ad_tracker.h"

#include "third_party/blink/renderer/core/inspector/console_message.h"

// CookieJar::IPCNeeded() calls SharedVersionGreaterThan(last_version_) to
// determine if the cookie string has changed, in which case it determines that
// IPC is needed. We adjust this to use an invalid version, because Ephemeral
// Storage can switch the cookie storage backend at runtime, so we can't use
// reduced IPCs when accessing cookies. This was previously handled by disabling
// kReduceCookieIPCs, but that feature flag is no longer available.
#define SharedVersionIsGreaterThan(VERSION) \
  SharedVersionIsGreaterThan(mojo::shared_memory_version::kInvalidVersion)

#define SetCookie SetCookie_ChromiumImpl  // Rename original method
#define Cookies Cookies_ChromiumImpl  // Rename original method

#include "src/third_party/blink/renderer/core/loader/cookie_jar.cc"  // IWYU pragma: export

#undef SharedVersionIsGreaterThan
#undef SetCookie
#undef Cookies

namespace blink {

  // Your Brave override of SetCookie
  void CookieJar::SetCookie(const String& value) {
    // Example: Log or filter cookie before calling upstream logic
    LOG(ERROR) << "[CookieJar::SetCookie] called!";
    // const String& modified_value = value + "-modified-new";
    ExecutionContext* context =document_->GetExecutionContext();
    AdTracker* tracker = AdTracker::FromExecutionContext(context);
    const bool is_ad = tracker && tracker->IsAdScriptInStack(AdTracker::StackType::kBottomAndTop);
        
    // Log to DevTools console
    String console_message = String::Format("[CookieJar::SetCookie] Called from ad? %s", is_ad ? "YES" : "NO");
    context->AddConsoleMessage(
        MakeGarbageCollected<ConsoleMessage>(
            mojom::ConsoleMessageSource::kOther,
            mojom::ConsoleMessageLevel::kInfo, console_message));

    // Call Chromium's renamed implementation
    SetCookie_ChromiumImpl(value);
  
    // Optionally, add post-processing or tracking here
  }

  String CookieJar::Cookies() {
    // Example: Log or filter cookie before calling upstream logic
    LOG(ERROR) << "[CookieJar::Cookies] called!";
    
    ExecutionContext* context =document_->GetExecutionContext();
    AdTracker* tracker = AdTracker::FromExecutionContext(context);
    const bool is_ad = tracker && tracker->IsAdScriptInStack(AdTracker::StackType::kBottomAndTop);
    
    // Log to DevTools console
    String console_message = String::Format("[CookieJar::Cookies] Called from ad? %s", is_ad ? "YES" : "NO");
    context->AddConsoleMessage(
        MakeGarbageCollected<ConsoleMessage>(
            mojom::ConsoleMessageSource::kOther,
            mojom::ConsoleMessageLevel::kInfo, console_message));

    // Call Chromium's renamed implementation
    return Cookies_ChromiumImpl();
  }
}