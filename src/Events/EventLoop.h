#ifndef H_EVENT_LOOP
#define H_EVENT_LOOP

#include <allegro5/allegro.h>
#include "Events/EventQueue.h"

class EventLoop : public EventQueue
{
    private:
        bool _active;
        bool _renderNeeded;
        ALLEGRO_EVENT _renderEvent;

        // Event Handlers
        void OnRenderNeeded();
        void OnStop();

    public:
        EventLoop();
        ~EventLoop();

        void SetupListen(EventQueueAccessor eQ);

        void Run();
        void Stop();
};
#endif
