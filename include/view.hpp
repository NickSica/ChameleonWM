#pragma once

extern "C" {
#include <wlr/types/wlr_surface.h>
#include <wlr/types/wlr_xdg_shell.h>
}

class ChamServer;

class ChamView
{
public:
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