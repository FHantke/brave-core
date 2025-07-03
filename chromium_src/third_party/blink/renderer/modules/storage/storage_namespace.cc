/*
 */

 #include "third_party/blink/renderer/modules/storage/storage_namespace.h"

 #define GetCachedArea GetCachedArea_ChromiumImpl
 #include "src/third_party/blink/renderer/modules/storage/storage_namespace.cc"
 #undef GetCachedArea
 
 namespace blink {
 
 scoped_refptr<CachedStorageArea> StorageNamespace::GetCachedArea(
     LocalDOMWindow* local_dom_window,
     mojo::PendingRemote<mojom::blink::StorageArea> storage_area,
     StorageContext context,
     bool ad_context) {
   // These values are persisted to logs. Entries should not be renumbered and
   // numeric values should never be reused.
   enum class CacheMetrics {
     kMiss = 0,    // Area not in cache.
     kHit = 1,     // Area with refcount = 0 loaded from cache.
     kUnused = 2,  // Cache was not used. Area had refcount > 0.
     kMaxValue = kUnused,
   };
 
   CacheMetrics metric = CacheMetrics::kMiss;
   scoped_refptr<CachedStorageArea> result;
   BlinkStorageKey storage_key = local_dom_window->GetStorageKey();
 
 
   // Create an alternative storage key with a nonce.
   if (!nonce_) {
     std::optional<base::UnguessableToken> token = base::UnguessableToken::Deserialize(0xABC, 0xDEF);
     if (!token.has_value())
       LOG(ERROR) << "Failed to deserialize nonce for storage key.";
     else
       nonce_ = token.value();
   }  
   
   if (ad_context) {
     // If this is an ad context, we use the ad storage key.
     storage_key = BlinkStorageKey::CreateWithNonce(
        storage_key.GetSecurityOrigin(), nonce_);
   }
 
   LOG(ERROR) << "StorageNamespace::GetCachedArea: in BRAVE"
   << "storage_key=" << storage_key.ToDebugString()
   << "context=" << (context == StorageContext::kStandard ? "Standard" : "StorageAccessAPI");
 
   // The Storage Access API needs to use the first-party version of the storage
   // key. For more see:
   // third_party/blink/renderer/modules/storage_access/README.md
   if (context == StorageContext::kStorageAccessAPI) {
     storage_key =
         BlinkStorageKey::CreateFirstParty(storage_key.GetSecurityOrigin());
   }
   auto cache_it = cached_areas_.find(&storage_key);
   if (cache_it != cached_areas_.end()) {
     metric = cache_it->value->HasOneRef() ? CacheMetrics::kHit
                                           : CacheMetrics::kUnused;
     result = cache_it->value;
   }
   if (IsSessionStorage()) {
     base::UmaHistogramEnumeration("Storage.SessionStorage.RendererAreaCacheHit",
                                   metric);
   } else {
     base::UmaHistogramEnumeration("LocalStorage.RendererAreaCacheHit", metric);
   }
 
   if (result)
     return result;
 
   controller_->ClearAreasIfNeeded();
   result = base::MakeRefCounted<CachedStorageArea>(
       IsSessionStorage() ? CachedStorageArea::AreaType::kSessionStorage
                          : CachedStorageArea::AreaType::kLocalStorage,
       storage_key, local_dom_window, this,
       /*is_session_storage_for_prerendering=*/false, std::move(storage_area));
   cached_areas_.insert(std::make_unique<const BlinkStorageKey>(storage_key),
                        result);
   return result;
 }
 
 }  // namespace blink
 