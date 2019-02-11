#define _POSIX_C_SOURCE 200809L
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <unistd.h>

#include <wayland-server.h>
#include <xkbcommon/xkbcommon.h>

#include "server.hpp"


/* Here so I can easily snip it- will remove later
#define class class_t
#define namespace namespace_t
#define delete delete_t
#define static

extern "C" {

}

#undef class
#undef namespace
#undef static
#undef delete
*/

extern "C" {
#include <wlr/util/log.h>
}

int main(int argc, char *argv[])
{
   wlr_log_init(WLR_DEBUG, NULL);
   char *startup_cmd = NULL;

   int c;
   while ((c = getopt(argc, argv, "s:h")) != -1)
   {
      switch (c)
      {
	 case 's':
	    startup_cmd = optarg;
	    break;
	 default:
	    printf("Usage: %s [-s startup command]\n", argv[0]);
	    return 0;
      }
   }
   if (optind < argc)
   {
      printf("Usage: %s [-s startup command]\n", argv[0]);
      return 0;
   }

   ChamServer server;

   server.newSocket();
   
   if (!wlr_backend_start(server.backend))
   {
      wlr_backend_destroy(server.backend);
      wl_display_destroy(server.wlDisplay);
      return 1;
   }

   if (startup_cmd) {
     if (fork() == 0) {
       execl("/bin/sh", "/bin/sh", "-c", startup_cmd, (void *)NULL);
     }
   }

   /*
   wl_display_init_shm(server.wlDisplay);
   wlr_gamma_control_manager_create(server.wlDisplay);
   wlr_screenshooter_create(server.wlDisplay);
   wlr_primary_selection_device_manager_create(server.wlDisplay);
   wlr_idle_create(server.wlDisplay);
   */

   wl_display_run(server.wlDisplay);

   wl_display_destroy_clients(server.wlDisplay);
   wl_display_destroy(server.wlDisplay);

   return 0;
}

