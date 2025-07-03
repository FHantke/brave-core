/* */

#ifndef BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_DOM_STORAGE_SPACE_H_
#define BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_DOM_STORAGE_SPACE_H_

#include "third_party/blink/renderer/modules/modules_export.h"

#define GetOrCreateSessionStorage               \
GetOrCreateSessionStorage_ChromiumImpl(   \
    ExceptionState& exception_state,    \
    mojo::PendingRemote<mojom::blink::StorageArea> storage_area_for_init) \
    const; \
    StorageArea* GetOrCreateSessionStorage

#define GetOrCreateLocalStorage               \
GetOrCreateLocalStorage_ChromiumImpl(   \
    ExceptionState& exception_state,    \
    mojo::PendingRemote<mojom::blink::StorageArea> storage_area_for_init) \
    const; \
    StorageArea* GetOrCreateLocalStorage

#include "src/third_party/blink/renderer/modules/storage/dom_window_storage.h"  // IWYU pragma: export

#undef GetOrCreateSessionStorage
#undef GetOrCreateLocalStorage

#endif  // BRAVE_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_DOM_STORAGE_SPACE_H_
