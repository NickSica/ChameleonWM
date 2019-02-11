#pragma once

class ChamSeat
{
   wlr_seat *seat;
   wl_listener newInput;
   wl_listener requestCursor;
   wl_list keyboards;
   enum cursorMode cursor_mode;
   ChamView *grabbedView;
   double grabX, grabY;
   int grabWidth, grabHeight;
   uint32_t resizeEdges;
}
