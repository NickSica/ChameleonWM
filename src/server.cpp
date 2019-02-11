#include "server.hpp"

#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_linux_dmabuf_v1.h>
#include <wlr/types/wlr_data_device.h>


ChamServer::ChamServer()
{
   wlDisplay = wl_display_create();
   // static_assert(wlDisplay, "Server display not initialized.");
   // wlEventLoop = wl_display_get_event_loop(wlDisplay);
   // static_assert(wlEventLoop, "Server backend not initialized.");
   backend = wlr_backend_autocreate(wlDisplay, NULL);
   // static_assert(backend, "Server backend not initialized.");
   renderer = wlr_backend_get_renderer(backend);

   wlr_compositor_create(wlDisplay, renderer);
   wlr_linux_dmabuf_v1_create(wlDisplay, renderer);
   wlr_data_device_manager_create(wlDisplay);
   outputLayout = wlr_output_layout_create();

   wl_list_init(&outputs);
   newOutput.notify = newOutputNotify;
   wl_signal_add(&backend->events.new_output, &newOutput);

   wl_list_init(&views);
   xdgShell = wlr_xdg_shell_create(wlDisplay);
   newXdgSurface.notify = newXdgSurfaceNotify;
   wl_signal_add(&xdgShell->events.new_surface, &newXdgSurface);

   cursor = wlr_cursor_create();
   wlr_cursor_attach_output_layout(cursor, outputLayout);

   cursorMgr = wlr_xcursor_manager_create(NULL, 24);
   wlr_xcursor_manager_load(cursorMgr, 1);

   cursorMotion.notify = serverCursorMotion;
   wl_signal_add(&cursor->events.motion, &cursorMotion);
   cursorMotionAbsolute.notify = serverCursorMotionAbsolute;
   wl_signal_add(&cursor->events.button, &cursorButton);
   cursorAxis.notify = serverCursorAxis;
   wl_signal_add(&cursor->events.axis, &cursorAxis);

   wl_list_init(&keyboards);
   newInput.notify = serverNewInput;
   wl_signal_add(&backend->events.new_input, &newInput);

   seat = wlr_seat_create(wlDisplay, "seat0");
   requestCursor.notify = seatRequestCursor;
   wl_signal_add(&seat->events.request_set_cursor, &requestCursor);
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

void ChamServer::focusView(ChamView *view, wlr_surface *surface)
{
   if(view == NULL)
   {
      return;
   }
   ChamServer *server = view->server;
   wlr_seat *seat = server->seat;
   wlr_surface *prevSurface = seat->keyboard_state.focused_surface;

   if(prevSurface == surface)
   {
      return;
   }

   if(prevSurface)
   {
      wlr_xdg_surface *previous =
	   wlr_xdg_surface_from_wlr_surface(seat->keyboard_state.focused_surface);
      wlr_xdg_toplevel_set_activated(previous, false);
   }

   wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat);
   wl_list_remove(&view->link);
   wl_list_insert(&server->views, &view->link);
   wlr_xdg_toplevel_set_activated(view->xdgSurface, true);
   wlr_seat_keyboard_notify_enter(seat, view->xdgSurface->surface,
				  keyboard->keycodes, keyboard->num_keycodes,
				  &keyboard->modifiers);
}


