#include "xdgshell.hpp"

#include <wlr/types/wlr_xdg_shell_v6.h>

ChamXdgShell::ChamXdgShell(wl_display *display)
{
   xdgShell = wlr_xdg_shell_v6_create(display);
   
}
