/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/renderer/core/farbling/brave_session_cache.h"
#include "third_party/blink/public/platform/web_content_settings_client.h"
#include "third_party/blink/renderer/core/frame/ad_tracker.h"
#include "ui/gfx/skia_span_util.h"

#define BRAVE_CANVAS_ASYNC_BLOB_CREATOR                    \
  AdTracker* tracker = AdTracker::FromExecutionContext(context_); \
  bool is_ad = tracker && tracker->IsAdScriptInStack(AdTracker::StackType::kBottomAndTop); \
  LOG(ERROR) << "[BRAVE_CANVAS_ASYNC_BLOB_CREATOR] Called from ad? " << (is_ad ? "YES" : "NO"); \
  if (is_ad) { \
    brave::BraveSessionCache::From(*context_).PerturbPixelsInternal( \
      gfx::SkPixmapToWritableSpan(src_data_)); \
  } \

#include "src/third_party/blink/renderer/core/html/canvas/canvas_async_blob_creator.cc"

#undef BRAVE_CANVAS_ASYNC_BLOB_CREATOR
