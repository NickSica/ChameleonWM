#pragma once
#include <wayland-server.h>
               
#define class class_t
#define namespace namespace_t
#define delete delete_t
#define static

extern "C" {
#include <wlr/backend.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/types/wlr_xcursor_manager.h>
}

#undef class
#undef namespace
#undef static
#undef delete

#include "view.hpp"

class ChamServer
{
private:
   enum ChamCursorMode {
      CHAM_CURSOR_PASSTHROUGH,
      CHAM_CURSOR_MOVE,
      CHAM_CURSOR_RESIZE,
   };
public:
   wl_display *wlDisplay;
   wlr_backend *backend;
   wlr_renderer *renderer;
   
   wlr_xdg_shell *xdgShell;
   wl_listener newXdgSurface;
   wl_list views;

   wlr_cursor *cursor;
   wlr_xcursor_manager *cursorMgr;
   wl_listener cursorMotion;
   wl_listener cursorMotionAbsolute;
   wl_listener cursorButton;
   wl_listener cursorAxis;

   wlr_seat *seat;
   wl_listener newInput;
   wl_listener requestCursor;
   wl_list keyboards;
   enum ChamCursorMode cursor_mode;
   ChamView *grabbedView;
   double grabX, grabY;
   int grabWidth, grabHeight;
   uint32_t resizeEdges;

   wlr_output_layout *outputLayout;
   wl_listener newOutput;
   wl_list outputs;

   ChamServer();
   int newSocket();
   static void newKeyboard(wlr_input_device *device);
   static void focusView(ChamView *view, wlr_surface *surface);
};













