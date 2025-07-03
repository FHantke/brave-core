/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

 #include "src/third_party/blink/renderer/core/xmlhttprequest/xml_http_request.h"
 #include "src/third_party/blink/renderer/core/xmlhttprequest/xml_http_request.cc"
 
 namespace blink {

bool XMLHttpRequest::InitSend(ExceptionState& exception_state) {
    // We need to check ContextDestroyed because it is possible to create a
    // XMLHttpRequest with already detached document.
    // TODO(yhirano): Fix this.
    if (!GetExecutionContext() || GetExecutionContext()->IsContextDestroyed()) {
      HandleNetworkError();
      ThrowForLoadFailureIfNeeded(exception_state,
                                  "Document is already detached.");
      return false;
    }
  
    ExecutionContext* context = GetExecutionContext();
    AdTracker* tracker = AdTracker::FromExecutionContext(context);
    const bool is_ad = tracker && tracker->IsAdScriptInStack(AdTracker::StackType::kBottomAndTop);
  
    if (is_ad) {
      HandleNetworkError();
      ThrowForLoadFailureIfNeeded(exception_state,
                                  "Document is ad context.");
      return false;
    }
    return InitSend_ChromiumImpl(exception_state);
}  
  
}  // namespace blink
  