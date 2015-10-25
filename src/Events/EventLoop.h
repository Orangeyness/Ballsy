#ifndef H_EVENTS_EVENT_LOOP
#define H_EVENTS_EVENT_LOOP

#include <allegro5/allegro.h>
#include "Events/EventQueue.h"
#include "Rendering/RenderQueue.h"

namespace Events
{
    class EventLoop : public EventQueue
    {
        private:
            bool _active;
            Rendering::RenderQueue _renderer;

        protected:
            void OnStop();

        public:
            EventLoop(ALLEGRO_EVENT_QUEUE* eventQueue, DispatchFilter filter);
            ~EventLoop();

            void ConnectEvents(EventBoy& boy);
            void DisconnectEvents(EventBoy& boy);

            void Run();
    };
}

#endif
