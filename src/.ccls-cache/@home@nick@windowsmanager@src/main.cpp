#define _POSIX_C_SOURCE 200809L
#include <cassert>
#include <iostream>
// #include <stdlib>
#include <chrono>

extern "C" {
    #include <wayland-server.h>
    #include <wlr/backend.h>
    // #include <wlr/render/wlr_renderer.h>
    #include <wlr/render/wlr_texture.h>
}
    
struct mcwServer {
    wl_display *wlDisplay;
    wl_event_loop *wlEventLoop;

    wlr_backend *backend;
};

int main()
{
    mcwServer server;
    
    server.wlDisplay = wl_display_create();
    assert(server.wlDisplay);
    server.wlEventLoop = wl_display_get_event_loop(server.wlDisplay);
    assert(server.wlEventLoop);

    server.backend = wlr_backend_autocreate(server.wlDisplay, NULL);
    assert(server.backend);

    if(!wlr_backend_start(server.backend))
    {
	std::cerr << stderr << "Failed to start backend\n";
    }

    wl_display_run(server.wlDisplay);
    wl_display_destroy(server.wlDisplay);

    return 0;
}
