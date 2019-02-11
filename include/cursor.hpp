#pragma once

#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_xcursor_manager.h>


struct cursorMode
{
   CURSOR_PASSTHROUGH,
   CURSOR_MOVE,
   CURSOR_RESIZE
};

class ChamCursor
{
   wlr_cursor *cursor;
   wlr_xcursor_manager *cursorMgr;
   wl_listener cursorMotion;
   wl_listener cursorMotionAbsolute;
   wl_listener cursorButton;
   wl_listener cursorAxis;

   wl_list link;
   wlr_input_device *device;

   ChamCursor();
   static void cursorMotionNotify(wl_listener *listener, void *data);
   static void cursorMotionAbsoluteNotify(wl_listener *listener, void *data);
   static void cursorAxisNotify(wl_listener *listener, void *data);
};
