#pragma once

#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_xcursor_manager.h>

class ChamCursor
{
private:
   wlr_cursor *cursor;
   wlr_xcursor_manager *cursorMgr;
   struct listeners
   {
      wl_listener cursorMotion;
      wl_listener cursorMotionAbsolute;
      wl_listener cursorButton;
      wl_listener cursorAxis;
   } cursorListeners;

   wl_list link;
   wlr_input_device *device;

   void cursorMotionNotify(wl_listener *listener, void *data);
   void cursorMotionAbsoluteNotify(wl_listener *listener, void *data);
   void cursorAxisNotify(wl_listener *listener, void *data);
   void processCursorMotion(listeners *listeners, uint32_t time);

public:
   ChamCursor();
   
};
