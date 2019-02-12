#pragma once

extern "C" {
#include <wlr/types/wlr_input_device.h>
}

class ChamKeyboard 
{
private:
   wl_list link;
   wlr_input_device *device;
   wl_listener modifiers;
   wl_listener key;

public:
   ChamKeyboard() {};
  
   void handleModifiers();
   bool handleKeybinding(xkb_keysym_t sym);
   void handleKey(wl_listener *listener, void *data);
};








