#pragma once

extern "C" {
#include <wlr/backend.h>
#include <wlr/types/wlr_data_device.h>
#include <wlr/types/wlr_linux_dmabuf_v1.h>
#include <wlr/types/wlr_xdg_shell_v6.h>
   
#define static
#include <wlr/types/wlr_compositor.h>
#include <wlr/render/wlr_renderer.h>
#undef static
}

#include "view.hpp"
#include "cursor.hpp"
#include "keyboard.hpp"
#include "seat.hpp"

class ChamServer
{

public:
   wl_display *wlDisplay;
   wlr_backend *backend;
   wlr_renderer *renderer;

   wlr_compositor *compositor;
   wlr_linux_dmabuf_v1 *dmabuf;
   
   wlr_xdg_shell_v6 *xdgShell;
   wl_listener newXdgSurface;
   wl_list views;

   ChamSeat seat;
   ChamCursor cursor;
   ChamKeyboard keyboard;
   ChamView grabbedView;

   wl_listener newInput;
   
   wlr_data_device_manager *dataDeviceMgr; 

   wlr_output_layout *outputLayout;
   wl_listener newOutput;
   wl_list outputs;

   ChamServer();
   int newSocket();
   void processNewOutput(wl_listener *listener, void *data);
   void processNewXdgSurface(wl_listener *listener, void *data);
   void processNewInput(wl_listener *listener, void *data);
   void requestCursor(wl_listener *listener, void *data);
   void processNewKeyboard(wlr_input_device *device);
   void focusView(ChamView *view, wlr_surface *surface);
};
