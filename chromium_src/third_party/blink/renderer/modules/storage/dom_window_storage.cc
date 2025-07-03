 #include "third_party/blink/renderer/modules/storage/dom_window_storage.h"

 #include "src/third_party/blink/renderer/modules/storage/dom_window_storage.cc"

#include "third_party/blink/renderer/core/frame/ad_tracker.h"

namespace blink {

StorageArea* DOMWindowStorage::GetOrCreateSessionStorage(
    ExceptionState& exception_state,
    mojo::PendingRemote<mojom::blink::StorageArea> storage_area_for_init)
    const {
  LocalDOMWindow* window = GetSupplementable();
  if (!window->GetFrame())
    return nullptr;

  if (!window->GetSecurityOrigin()->CanAccessSessionStorage()) {
    if (window->IsSandboxed(network::mojom::blink::WebSandboxFlags::kOrigin))
      exception_state.ThrowSecurityError(StorageArea::kAccessSandboxedMessage);
    else if (window->Url().ProtocolIs("data"))
      exception_state.ThrowSecurityError(StorageArea::kAccessDataMessage);
    else
      exception_state.ThrowSecurityError(StorageArea::kAccessDeniedMessage);
    return nullptr;
  }

  if (window->GetFrame()->Client()->IsDomStorageDisabled()) {
    return nullptr;
  }

  ExecutionContext* context = window->GetExecutionContext();
  AdTracker* tracker = AdTracker::FromExecutionContext(context);
  const bool is_ad = tracker && tracker->IsAdScriptInStack(AdTracker::StackType::kBottomAndTop);

  if (is_ad) {
      /* IN AD CONTEXT */
      if (session_ad_storage_)
        return session_ad_storage_.Get();

      StorageNamespace* storage_namespace = StorageNamespace::From(window->GetFrame()->GetPage());
      if (!storage_namespace)
        return nullptr;

      scoped_refptr<CachedStorageArea> cached_storage_area = storage_namespace->GetCachedArea(
                            window, std::move(storage_area_for_init),
                            StorageNamespace::StorageContext::kStandard, /*ad_context=*/true);

      session_ad_storage_ = StorageArea::Create(window, std::move(cached_storage_area),
                          StorageArea::StorageType::kSessionStorage);

      return session_ad_storage_.Get();
  }
  return GetOrCreateSessionStorage_ChromiumImpl(
      exception_state, std::move(storage_area_for_init));
}

StorageArea* DOMWindowStorage::GetOrCreateLocalStorage(
    ExceptionState& exception_state,
    mojo::PendingRemote<mojom::blink::StorageArea> storage_area_for_init)
    const {
  LocalDOMWindow* window = GetSupplementable();
  if (!window->GetFrame())
    return nullptr;

  if (!window->GetSecurityOrigin()->CanAccessLocalStorage()) {
    if (window->IsSandboxed(network::mojom::blink::WebSandboxFlags::kOrigin))
      exception_state.ThrowSecurityError(StorageArea::kAccessSandboxedMessage);
    else if (window->Url().ProtocolIs("data"))
      exception_state.ThrowSecurityError(StorageArea::kAccessDataMessage);
    else
      exception_state.ThrowSecurityError(StorageArea::kAccessDeniedMessage);
    return nullptr;
  }

  if (!window->GetFrame()->GetSettings()->GetLocalStorageEnabled()) {
    return nullptr;
  }

  if (window->GetFrame()->Client()->IsDomStorageDisabled()) {
    return nullptr;
  }

  ExecutionContext* context = window->GetExecutionContext();
  AdTracker* tracker = AdTracker::FromExecutionContext(context);
  const bool is_ad = tracker && tracker->IsAdScriptInStack(AdTracker::StackType::kBottomAndTop);

  LOG(ERROR) << "[DOMWindowStorage::GetOrCreateLocalStorage] "
            << "get or create localStorage called from ad? " << (is_ad ? "YES" : "NO");

  if (is_ad) {
    /* IN AD CONTEXT */
    if (local_ad_storage_)
      return local_ad_storage_.Get();
    
    Page* page = window->GetFrame()->GetPage();
    auto* security_origin =
      page->MainFrame()->GetSecurityContext()->GetSecurityOrigin();
    String domain = security_origin->RegistrableDomain();

    // RegistrableDomain might return an empty string if this host is an IP
    // address or a file URL.
    if (domain.empty()) {
      url::Origin origin = url::Origin::Create(GURL(window->Url()));
      domain = String::FromUTF8(origin.Serialize());
    }

    // String storage_id = security_origin->ToString() + "/ad_storage_"; // + nonce;
    String storage_id = domain + "/ad_storage_";
    
    StorageNamespace* storage_namespace = StorageController::GetInstance()->CreateSessionStorageNamespace(
      *page,
      storage_id
    );    

    if (!storage_namespace)
      return nullptr;

    scoped_refptr<CachedStorageArea> cached_storage_area = storage_namespace->GetCachedArea(
      window, std::move(storage_area_for_init), StorageNamespace::StorageContext::kStandard, /*ad_context=*/true);
    
    local_ad_storage_ = StorageArea::Create(window, std::move(cached_storage_area),
                            StorageArea::StorageType::kSessionStorage);
                                    
    return local_ad_storage_.Get();                    
  }

  return GetOrCreateLocalStorage_ChromiumImpl(
      exception_state, std::move(storage_area_for_init));
}

}  // namespace blink
