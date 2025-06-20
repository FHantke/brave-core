/* Copyright (c) 2025 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

 #ifndef BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_IMAGE_ELEMENT_H_
 #define BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_IMAGE_ELEMENT_H_
 
 #define SelectSourceURL           \
 SelectSourceURL_ChromiumImpl( \
     ImageLoader::UpdateFromElementBehavior behavior); \
 void SelectSourceURL

 #include "src/third_party/blink/renderer/core/html/html_image_element.h"  // IWYU pragma: export
 
 #undef SelectSourceURL
 
 #endif  // BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_IMAGE_ELEMENT_H_
 