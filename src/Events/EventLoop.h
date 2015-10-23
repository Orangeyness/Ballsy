#ifndef H_EVENTS_EVENT_LOOP
#define H_EVENTS_EVENT_LOOP

#include <allegro5/allegro.h>
#include "Events/EventQueue.h"

namespace Events
{
    class EventLoop : public EventQueue
    {
        private:
            bool _active;
            bool _renderNeeded;
            ALLEGRO_EVENT _renderEvent;

        protected:
            void ConnectEvents();
            void DisconnectEvents();

            // Event Handlers
            void OnRenderNeeded();
            void OnStop();

        public:
            EventLoop(ALLEGRO_EVENT_QUEUE* eventQueue, DispatchFilter filter);
            ~EventLoop();

            void Run();
            void Stop();
    };
}

#endif
