#pragma once

#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_xcursor_manager.h>

class ChamCursor
{
private:
   wlr_cursor *cursor;
   wlr_xcursor_manager *cursorMgr;

   enum enumCursorMode
   {
      CURSOR_PASSTHROUGH,
      CURSOR_MOVE,
      CURSOR_RESIZE
   } cursorMode;
   
   struct listeners
   {
      wl_listener cursorMotion;
      wl_listener cursorMotionAbsolute;
      wl_listener cursorButton;
      wl_listener cursorAxis;
   } cursorListeners;

   wl_list link;
   wlr_input_device *device;

public:
   ChamCursor();
   void processCursorMotion(wlr_event_pointer_motion *event);
   void processCursorMove(wlr_event_pointer_motion *event);
   void processCursorResize(wlr_event_pointer_motion *event);

   operator wlr_cursor*() { return cursor; }
};
