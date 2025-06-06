#ifndef BRAVE_RENDERER_LOADER_BRAVE_COOKIE_JAR_H_
#define BRAVE_RENDERER_LOADER_BRAVE_COOKIE_JAR_H_


#define SetCookie                     \
  SetCookie_ChromiumImpl(const String& value); \
  String Cookies_ChromiumImpl(); \
  void SetCookie


#include "src/third_party/blink/renderer/core/loader/cookie_jar.h"
#undef SetCookie
// #undef Cookies

#endif  // BRAVE_RENDERER_LOADER_BRAVE_COOKIE_JAR_H_
