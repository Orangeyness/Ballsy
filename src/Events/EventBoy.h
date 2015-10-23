#ifndef H_EVENTS_EVENT_BOY
#define H_EVENTS_EVENT_BOY

#include "Events/Dispatcher.h"
#include "Events/DispatcherProxy.h"
#include "Events/SourceGroup.h"

#include <allegro5/allegro.h>

namespace Events
{

    class EventBoy
    {
        friend class EventQueue;
        friend Dispatcher;

        private:
            ListenerHandle _listener;
            Dispatcher* _dispatcher;
            SourceGroup* _sources;
            ALLEGRO_EVENT_SOURCE* _internalSource;

        protected:
            EventBoy(ListenerHandle _listener, Dispatcher* dispatcher, SourceGroup* sources, ALLEGRO_EVENT_SOURCE* internalSource);
            EventBoy(Dispatcher* dispatcher, SourceGroup* sources, ALLEGRO_EVENT_SOURCE* internalSource);
            void ReBind(ListenerHandle _listener);

        public:
            EventBoy();

            bool Enabled();

            DispatcherProxy Listen();

            DispatcherProxy Listen(intptr_t id);

            void StopListening();

            void TalkFrom(ALLEGRO_EVENT_SOURCE* source);
            void StopTalking(ALLEGRO_EVENT_SOURCE* source);
            void StopTalking();

            void Talk(ALLEGRO_EVENT& event);
            void Talk(ALLEGRO_EVENT_TYPE type);
    };

}
#endif
