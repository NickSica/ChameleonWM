#include "cursor.hpp"

#include <wayland-server.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_xcursor_manager.h>

#include "server.hpp"

extern ChamServer *server;

static void cursorMotionNotify(wl_listener *, void *data)
{
   wlr_event_pointer_motion *event = static_cast<wlr_event_pointer_motion *>(data);
   
   server->cursor.processCursorMotion(event);
}

static void cursorMotionAbsoluteNotify(wl_listener *listener, void *data)
{

}

static void cursorAxisNotify(wl_listener *listener, void *data)
{
   
}

ChamCursor::ChamCursor()
{
   cursor = wlr_cursor_create();
   cursorMgr = wlr_xcursor_manager_create(NULL, 24);
   wlr_xcursor_manager_load(cursorMgr, 1);
   
   cursorListeners.cursorMotion.notify = cursorMotionNotify;
   wl_signal_add(&cursor->events.motion, &cursorListeners.cursorMotion);

   cursorListeners.cursorMotionAbsolute.notify = cursorMotionAbsoluteNotify;
   wl_signal_add(&cursor->events.motion_absolute, &cursorListeners.cursorMotionAbsolute);
   
   cursorListeners.cursorAxis.notify = cursorAxisNotify;
   wl_signal_add(&cursor->events.axis, &cursorListeners.cursorAxis);
}

void ChamCursor::processCursorMotion(wlr_event_pointer_motion *event)
{
   if(cursorMode == CURSOR_MOVE)
   {
      wlr_cursor_move(cursor, event->device, event->delta_x, event->delta_y);
      processCursorMove(event);
      return;
   }
   else if(cursorMode == CURSOR_RESIZE)
   {
      processCursorResize(event);
      return;
   }
}

void ChamCursor::processCursorMove(wlr_event_pointer_motion *event)
{
   server->grabbedView->x = server->cursor->x - server->grab_x;
   server->grabbedView->y = server->cursor->y - server->grab_y;
}

void ChamCursor::processCursorResize(wlr_event_pointer_motion *event) {}


