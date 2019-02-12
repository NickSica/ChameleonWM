#pragma once

#include <wlr/types/wlr_seat.h>
#include "view.hpp"

class ChamSeat
{
private:
   wlr_seat *seat;
   
   wl_listener requestCursor;
   wl_list keyboards;

   ChamView *grabbedView;
   double grabX, grabY;
   int grabWidth, grabHeight;
   uint32_t resizeEdges;
public:
   ChamSeat();
   wlr_seat *getSeat() { return seat; };
};
