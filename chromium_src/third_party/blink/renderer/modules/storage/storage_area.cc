/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/modules/storage/storage_area.h"
#include "base/check.h"

#define setItem setItem_ChromiumImpl
#define getItem getItem_ChromiumImpl

#include "src/third_party/blink/renderer/modules/storage/storage_area.cc"

#undef getItem
#undef setItem


#include "brave/third_party/blink/renderer/core/brave_page_graph/blink_probe_types.h"

namespace blink {

PageGraphObject ToPageGraphObject(StorageArea* storage_area) {
  DCHECK(storage_area);
  switch (storage_area->storage_type()) {
    case StorageArea::StorageType::kLocalStorage: {
      return PageGraphObject().Set("storage_type", base::Value("localStorage"));
    }
    case StorageArea::StorageType::kSessionStorage: {
      return PageGraphObject().Set("storage_type",
                                   base::Value("sessionStorage"));
    }
  }
}

NamedPropertySetterResult StorageArea::setItem(
  const String& key,
  const String& value,
  ExceptionState& exception_state) {
  if (storage_type_ == StorageType::kLocalStorage) {
    LOG(ERROR) << "[StorageArea::setItem] localStorage called with key: " << key
    << ", value: " << value;
  } else if (storage_type_ == StorageType::kSessionStorage) {
    LOG(ERROR) << "[StorageArea::setItem] sessionStorage called with key: " << key
    << ", value: " << value;
  }

  return setItem_ChromiumImpl(key, value, exception_state);
}

String StorageArea::getItem(const String& key,
                          ExceptionState& exception_state) const {
  if (storage_type_ == StorageType::kLocalStorage) {
    LOG(ERROR) << "[StorageArea::getItem] sessionStorage called with key: " << key;
  } else if (storage_type_ == StorageType::kSessionStorage) {
    LOG(ERROR) << "[StorageArea::getItem] sessionStorage called with key: " << key;
  }
  return getItem_ChromiumImpl(key, exception_state);
}


}  // namespace blink


