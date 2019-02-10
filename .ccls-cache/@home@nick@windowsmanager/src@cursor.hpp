
struct cursorMode {
   CURSOR_PASSTHROUGH,
   CURSOR_MOVE,
   CURSOR_RESIZE
};

struct wmPointer {
   wl_list link;
   wmServer *server;
   wlr_input_device *device;
};
