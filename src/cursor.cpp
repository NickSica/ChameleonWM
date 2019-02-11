#include "cursor.hpp"

#include <wlr/types/wlr_cursor.h>
#include <wayland-server.h>

ChamCursor::ChamCursor()
{
   cursor = wlr_cursor_create();
   cursorListeners.cursorMotion.notify = cursorMotionNotify;
   wl_signal_add(cursor->events.motion, cursorMotion);

   cursorListeners.cursorMotionAbsolute.notify = cursorMotionAbsoluteNotify;
   wl_signal_add(cursor->events.motion_absolute, cursorMotionAbsolute);
   
   cursorListeners.cursorAxis.notify = cursorAxisNotify;
   wl_signal_add(cursor->events.axis, cursorAxis);
}

void ChamCursor::cursorMotionNotify(wl_listener *listener, void *data)
{
   ChamCursor::listeners *cursorListeners =  wl_container_of(listener, cursorListeners, cursorMotion);
   wlr_event_pointer_motion *event = (wlr_event_pointer_motion *) data;

   wlr_cursor_move(cursor, event->device, event->delta_x, event->delta_y);
   processCursorMotion(cursorListeners, event->time_msec);
}

void ChamCursor::cursorMotionAbsoluteNotify(wl_listener *listener, void *data)
{

}

void ChamCursor::cursorAxisNotify(wl_listener *listener, void *data)
{
   
}

void ChamCursor::processCursorMotion(ChamCursor::listeners *listeners, uint32_t time)
{
   
}

