#ifndef H_SHUTDOWN_LISTENER
#define H_SHUTDOWN_LISTENER

#include "Events/EventLoop.h"
#include <allegro5/allegro.h>

class ShutdownListener
{
    private:
        void Shutdown(EventQueueAccessor eQ);
        void Pause(EventQueueAccessor eQ);
        void Resume(EventQueueAccessor eQ);

    public:
        void SetupListen(EventQueueAccessor eQ);
};

#endif
