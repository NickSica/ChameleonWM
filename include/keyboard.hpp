#pragma once

#include "server.hpp"

extern "C" {
#include <wlr/types/wlr_input_device.h>
}

class ChamKeyboard 
{
   wl_list link;
   ChamServer *server;
   wlr_input_device *device;
   wl_listener modifiers;
   wl_listener key;

   static void keyboardHandleModifiers(wl_listener *listener, void *data);
   static bool handleKeybinding(ChamServer *server, xkb_keysym_t sym);
   static void keyboardHandleKey(wl_listener *listener, void *data);
};