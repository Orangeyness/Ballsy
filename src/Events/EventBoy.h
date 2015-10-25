#ifndef H_EVENTS_EVENT_BOY
#define H_EVENTS_EVENT_BOY

#include "Events/Dispatcher.h"
#include "Events/DispatcherProxy.h"
#include "Events/SourceGroup.h"
#include "Events/EventReader.h"
#include "Events/EventTypes.h"

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
            EventBoy();

            void ReBind(ListenerHandle _listener);

        public:
            bool Enabled();

            DispatcherProxy Listen();

            DispatcherProxy Listen(intptr_t id);

            void StopListening();

            void TalkFrom(ALLEGRO_EVENT_SOURCE* source);
            void StopTalking(ALLEGRO_EVENT_SOURCE* source);
            void StopTalking();

            template<typename T>
            void Talk(T event);
            void Talk(UserEventId type);
            void Talk(ALLEGRO_EVENT& type);
            void Talk(ALLEGRO_EVENT_TYPE type);

            template<typename T>
            void Register(T& client);
           
            template<typename T>
            void Register(T* client);

            template<typename T>
            void Unregister(T& client);
           
            template<typename T>
            void Unregister(T* client);
    };

    template<typename T>
    void EventBoy::Talk(T event)
    {
        event.Transmit(_internalSource);
    }

    template<typename T>
    void EventBoy::Register(T& client)
    {
        auto originalListener = _listener;
        ReBind(static_cast<ListenerHandle>(&client));

        client.ConnectEvents(*this);

        ReBind(originalListener);
    }

    template<typename T>
    void EventBoy::Register(T* client)
    {
        auto originalListener = _listener;
        ReBind(static_cast<ListenerHandle>(client));

        client->ConnectEvents(*this);

        ReBind(originalListener);
    }

    template<typename T>
    void EventBoy::Unregister(T& client)
    {
        auto originalListener = _listener;
        ReBind(static_cast<ListenerHandle>(&client));

        client.DisconnectEvents(*this);

        ReBind(originalListener);
    }

    template<typename T>
    void EventBoy::Unregister(T* client)
    {
        auto originalListener = _listener;
        ReBind(static_cast<ListenerHandle>(client));

        client->DisconnectEvents(*this);

        ReBind(originalListener);
    }
}
#endif
