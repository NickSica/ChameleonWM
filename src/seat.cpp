#include "seat.hpp"

#include <wayland-server.h>

#include "server.hpp"

static void requestCursorNotify(wl_listener *, void *data)
{
   
}

static void newInputNotify(wl_listener *, void *data)
{

}

ChamSeat::ChamSeat()
{
   seat = wlr_seat_create(server->wlDisplay, "seat0");

   requestCursor.notify = requestCursorNotify;
   wl_signal_add(&seat->events.request_set_cursor, &requestCursor);
   wl_list_init(&keyboards);
}

