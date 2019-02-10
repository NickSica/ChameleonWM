#define class _class
#define namespace _namespace
#define delete _delete
#define static

extern "C" {
#include <wlr/types/wlr_surface.h>
#include <wlr/types/wlr_xdg_shell.h>
}

#undef class
#undef namespace
#undef static
#undef delete

class ChamServer;

class ChamView
{
private:
   wl_list link;
   ChamServer *server;
   wlr_xdg_surface *xdgSurface;
   wl_listener destroy;

   wl_listener map;
   wl_listener unmap;
   bool mapped;
   
   wl_listener requestMove;
   wl_listener requestResize;
   int x, y;
};



