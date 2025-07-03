/* */

#ifndef BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_STORAGE_NAMESPACE_H_
#define BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_STORAGE_NAMESPACE_H_

#include "third_party/blink/renderer/modules/modules_export.h"

#define GetCachedArea               \
GetCachedArea_ChromiumImpl(         \
  LocalDOMWindow* local_dom_window, \
  mojo::PendingRemote<mojom::blink::StorageArea> storage_area = {}, \
  StorageContext context = StorageContext::kStandard,               \
  bool ad_context = false);         \
  scoped_refptr<CachedStorageArea> GetCachedArea

#include "src/third_party/blink/renderer/modules/storage/storage_namespace.h"  // IWYU pragma: export
#undef GetCachedArea

#endif  // BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_STORAGE_NAMESPACE_H_
