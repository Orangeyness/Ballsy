#ifndef H_SHUTDOWN_LISTENER
#define H_SHUTDOWN_LISTENER

#include "EventLoop.h"
#include <allegro5/allegro.h>

class ShutdownListener
{
    private:
        EventCallbackResult Shutdown(const ALLEGRO_EVENT& event);

    public:
        void SetEventLoop(EventLoopListenerAdder loop);
};

#endif
