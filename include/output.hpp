




struct wmOutput {
   wl_list link;
   wmServer *server;
   wlr_output *wlrOutput;
   wl_listener frame;
};

static void outputFrameNotify(wl_listener *listener, void *data)
{
   wmOutput *output = wl_container_of(listener, output, frame);
   wlr_output *wlrOutput = (wlr_output *)data;
   wlr_renderer *renderer = wlr_backend_get_renderer(wlrOutput->backend);

   timespec *now;
   clock_gettime(CLOCK_MONOTONIC, now);

   // Pretty color calculation
   long ms = (now->tv_sec - output->lastFrame.tv_sec) * 1000 +
             (now->tv_nsec - output->lastFrame.tv_nsec) / 1000000;
   int inc = (output->dec + 1) % 3;
   output->color[inc] += ms / 2000.0f;
   output->color[output->dec] -= ms / 2000.0f;
   if (output->color[output->dec] < 0.0f)
   {
      output->color[inc] = 1.0f;
      output->color[output->dec] = 0.0f;
      output->dec = inc;
   }

   wlr_output_make_current(wlrOutput, NULL);
   wlr_renderer_begin(renderer, wlrOutput->width, wlrOutput->height);

   wlr_renderer_clear(renderer, &output->color);
   wlr_output_swap_buffers(wlrOutput, NULL, NULL);
   wlr_renderer_end(renderer);

   output->lastFrame = *now;
}

static void outputDestroyNotify(wl_listener *listener, void *data)
{
   wmOutput *output = wl_container_of(listener, output, destroy);
   wl_list_remove(&output->link);
   wl_list_remove(&output->destroy.link);
   wl_list_remove(&output->frame.link);
   free(output);
}

static void newOutputNotify(wl_listener *listener, void *data)
{
   wmServer *server = wl_container_of(listener, server, newOutput);
   wlr_output *wlrOutput = (wlr_output *)data;

   if (wl_list_length(&wlrOutput->modes) > 0)
   {
      wlr_output_mode *mode =
         wl_container_of((&wlrOutput->modes)->prev, mode, link);
      wlr_output_set_mode(wlrOutput, mode);
   }

   wmOutput *output = new wOutput();
   clock_gettime(CLOCK_MONOTONIC, &output->lastFrame);
   output->server = server;
   output->wlrOutput = wlrOutput;
   output->color[0] = 1.0;
   output->color[3] = 1.0;
   wl_list_insert(&server->outputs, &output->link);

   output->destroy.notify = outputDestroyNotify;
   wl_signal_add(&wlrOutput->events.destroy, &output->destroy);

   output->frame.notify = outputFrameNotify;
   wl_signal_add(&wlrOutput->events.frame, &output->frame);

   wlr_output_create_global(wlrOutput);
}
