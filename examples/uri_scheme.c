#include "webview.h"
#include <stddef.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#define URI_SCHEME "custom-scheme"

void handler(void *req, const char *uri, void *arg) {
  webview_t w = (webview_t)arg;
  if (!strcmp(uri, URI_SCHEME ":index")) {
    webview_uri_scheme_respond(w, req, 0, "<h1>Index</h1><a href=\""
      URI_SCHEME ":other\">Go to other</a>", -1, "text/html");
  } else if (!strcmp(uri, URI_SCHEME ":other")) {
    webview_uri_scheme_respond(w, req, 0, "<h1>Other</h1><a href=\""
      URI_SCHEME ":index\">Go to index</a>", -1, "text/html");
  } else {
    webview_uri_scheme_respond(w, req, 1, "<h1>404</h1>", -1, "text/html");
  }
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
                   int nCmdShow) {
#else
int main() {
#endif
  webview_t w = webview_create(0, NULL);
  webview_set_title(w, "URI Scheme Example");
  webview_set_size(w, 480, 320, WEBVIEW_HINT_NONE);
  webview_register_uri_scheme(w, URI_SCHEME, handler, w);
  webview_navigate(w, URI_SCHEME ":index");
  webview_run(w);
  webview_destroy(w);
  return 0;
}
