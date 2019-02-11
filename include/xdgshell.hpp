#pragma once

#include <cstdint>

#include <wayland-server.h>
#include <wlr/types/wlr_xdg_shell_v6.h>

class ChamXdgShell
{
private:
   wlr_xdg_shell_v6 *xdgShell;
   
   wl_global *global;
   wl_list clients;
   wl_list popup_grabs;
   uint32_t ping_timeout;

   wl_listener display_destroy;

   struct {
      wl_signal new_surface;
      wl_signal destroy;
   } events;
   
   void* data;
public:
   ChamXdgShell(wl_display *display);
};
