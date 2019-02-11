#include "keyboard.hpp"

void ChamKeyboard::keyboardHandleModifiers(wl_listener *listener, void *data)
{
   wmKeyboard *keyboard = wl_container_of(listener, keyboard, modifiers);
   wlr_seat_set_keyboard(keyboard->server->seat, keyboard->device);
   wlr_seat_keyboard_notify_modifiers(keyboard->server->seat,
				      &keyboard->device->keyboard->modifiers);
}

bool ChamKeyboard::handleKeybinding(ChamServer *server, xkb_keysym_t sym)
{
   switch (sym)
   {
      case XKB_KEY_Escape:
	 wl_display_terminate(server->wlDisplay);
	 break;
      case XKB_KEY_F1:
	 if (wl_list_length(&server->views) < 2)
	 {
	    break;
	 }
	 ChamView currView = wl_container_of(server->views.next, currView, link);
	 ChamView nextView = wl_container_of(currView->link.next, nextView, link);
	 focusView(nextView, nextView->xdgSurface->surface);
	 wl_list_remove(&currView->link);
	 wl_list_insert(server->views.prev, &currView->link);
	 break;
      default:
	 return false;
   }
   return true;
}

void ChamKeyboard::keyboardHandleKey(wl_listener *listener, void *data)
{
   wmKeyboard *keyboard = wl_container_of(listener, keyboard, key);
   wmServer *server = keyboard->server;
   wlr_event_keyboard_key *event = data;
   wlr_seat *seat = server->seat;

   uint32_t keycode = event->keycode + 8;
   const xkb_keysym_t *syms;
   int nsyms = xkb_state_key_get_syms(keyboard->device->keyboard->xkb_state, keycode, &syms);

   bool handled = false;
   uint32_t modifiers = wlr_keyboard_get_modifiers(keyboard->device->keyboard);
   if((modifiers & WLR_MODIFIER_ALT) && event->state == WLR_BUTTON_PRESSED)
   {
      for(int i = 0; i < nsyms; i++)
      {
	 handled = handleKeybinding(server, syms[i]);
      }
   }

   if(!handled)
   {
      wlr_seat_set_keyboard(seat, keyboard->device);
      wlr_seat_keyboard_notify_key(seat, event->time_msec, event->keycode, event->state);
   }
}