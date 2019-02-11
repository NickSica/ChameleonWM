#include "cursor.hpp"

#include <wlr/types/wlr_cursor.h>
#include <wayland-server.h>

ChamCursor::ChamCursor()
{
   cursor = wlr_cursor_create();
   wl_signal_add(cursor->events.motion, cursorMotion);
   wl_signal_add(cursor->events.axis, cursorAxis);
}

void ChamCursor::cursorMotionNotify(wl_listener *listener, void *data)
{
   
}

void ChamCursor::cursorMotionAbsoluteNotify(wl_listener *listener, void *data)
{

}

void ChamCursor::cursorAxisNotify(wl_listener *listener, void *data)
{
   
}

