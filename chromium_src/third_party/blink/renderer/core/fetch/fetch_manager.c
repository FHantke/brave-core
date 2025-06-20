/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "src/third_party/blink/renderer/core/fetch/fetch_manager.h"

#define Fetch(...) Fetch_ChromiumImpl(__VA_ARGS__)
#include "src/third_party/blink/renderer/core/fetch/fetch_manager.c"
#undef Fetch

namespace blink {
 
ScriptPromise<Response> FetchManager::Fetch(ScriptState* script_state, // test
                                        FetchRequestData* request,
                                        AbortSignal* signal,
                                        ExceptionState& exception_state) {
    DCHECK(signal);

    // ExecutionContext* context =document_->GetExecutionContext();
    ExecutionContext* execution_context = GetExecutionContext();
    AdTracker* tracker = AdTracker::FromExecutionContext(execution_context);  
    const bool is_ad = tracker && tracker->IsAdScriptInStack(AdTracker::StackType::kBottomAndTop);

    if (is_ad) {
        return ScriptPromise<Response>::Reject(script_state,
        signal->reason(script_state));
    }

    return Fetch_ChromiumImpl(script_state, request, signal, exception_state);
}
  
}  // namespace blink
  