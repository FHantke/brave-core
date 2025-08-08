/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/core/html/html_image_loader.h"

#include "src/third_party/blink/renderer/core/html/html_image_element.cc"

namespace blink {
 
void HTMLImageElement::SelectSourceURL(
    ImageLoader::UpdateFromElementBehavior behavior) {
    LOG(ERROR) << "[HTMLImageElement::SelectSourceURL] BRAVE called!";
    if (!GetDocument().IsActive())
        return;

    ExecutionContext* context = GetExecutionContext();
    AdTracker* tracker = AdTracker::FromExecutionContext(context);
    const bool is_ad = tracker && tracker->IsAdScriptInStack(AdTracker::StackType::kBottomAndTop);
    LocalFrame* frame = GetDocument().GetFrame();
    const bool is_ad_frame = frame && frame->IsAdFrame();
    const bool is_ad_tracker_tagged_element = Element::IsAdTrackerTagged();
    const bool is_ad_tracker_tagged_node = Node::IsAdTrackerTaggedNode();

    LOG(ERROR) << "[HTMLImageElement::SelectSourceURL]: "
    << "Best fit image URL: " << best_fit_image_url_.GetString()
    << ", is ad: " << is_ad
    << ", is ad frame: " << is_ad_frame;

    if (is_ad || is_ad_frame || is_ad_tracker_tagged_node || is_ad_tracker_tagged_element) {
    // if (is_ad || is_ad_frame) {
        LOG(ERROR) << "[HTMLImageElement::SelectSourceURL] Blocked image load from JS context.";
        return;
    }
    SelectSourceURL_ChromiumImpl(behavior);
}
 
 }  // namespace blink
 