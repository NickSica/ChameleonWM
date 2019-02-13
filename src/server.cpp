#include "server.hpp"

extern "C" {
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_data_device.h>
#include <wlr/types/wlr_keyboard.h>
#include <wlr/types/wlr_linux_dmabuf_v1.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_xdg_shell_v6.h>
}

static void newOutputNotify(wl_listener *listener, void *data)
{
   
}

static void newXdgSurfaceNotify(wl_listener *listener, void *data)
{
   
}

static void newInputNotify(wl_listener *listener, void *data)
{

}

static void requestCursorNotify(wl_listener *listener, void *data)
{
   
}

ChamServer::ChamServer()
{
   wlDisplay = wl_display_create();
   backend = wlr_backend_autocreate(wlDisplay, NULL);
   renderer = wlr_backend_get_renderer(backend);

   compositor = wlr_compositor_create(wlDisplay, renderer);
   dmabuf = wlr_linux_dmabuf_v1_create(wlDisplay, renderer);
   dataDeviceMgr = wlr_data_device_manager_create(wlDisplay);
   outputLayout = wlr_output_layout_create();

   wl_list_init(&outputs);
   newOutput.notify = newOutputNotify;
   wl_signal_add(&backend->events.new_output, &newOutput);

   wl_list_init(&views);
   xdgShell = wlr_xdg_shell_v6_create(wlDisplay);
   newXdgSurface.notify = newXdgSurfaceNotify;
   wl_signal_add(&xdgShell->events.new_surface, &newXdgSurface);

   wlr_cursor_attach_output_layout((wlr_cursor*) cursor, outputLayout);
}

int ChamServer::newSocket()
{
   const char *socket = wl_display_add_socket_auto(wlDisplay);
   if (!socket)
   {
      wlr_backend_destroy(backend);
      return 1;
   }
   printf("Running compositor on wayland display '%s'\n", socket);
   setenv("WAYLAND_DISPLAY", socket, true);

   return 0;
}

void ChamServer::focusView(ChamView *targetView, wlr_surface *surface)
{
   if(targetView == NULL)
   {
      return;
   }
   wlr_surface *prevSurface = ((wlr_seat *)seat)->keyboard_state.focused_surface;

   if(prevSurface == surface)
   {
      return;
   }

   if(prevSurface)
   {
      wlr_xdg_surface_v6 *previous =
	 wlr_xdg_surface_v6_from_wlr_surface(((wlr_seat *)seat)->keyboard_state.focused_surface);
      wlr_xdg_toplevel_v6_set_activated(previous, false);
   }

   wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat);
   wl_list_remove(&targetView->link);
   wl_list_insert(&views, &targetView->link);
   wlr_xdg_toplevel_v6_set_activated(targetView->xdgSurface, true);
   wlr_seat_keyboard_notify_enter(seat, targetView->xdgSurface->surface,
				  keyboard->keycodes, keyboard->num_keycodes,
				  &keyboard->modifiers);
}

ChamServer *server;
