#ifndef H_EVENTS_EVENT_QUEUE
#define H_EVENTS_EVENT_QUEUE

#include "Events/EventBoy.h"
#include "Events/Dispatcher.h"
#include "Events/EventFilters.h"
#include "Events/SourceGroup.h"

#include <allegro5/allegro.h>

namespace Events
{
    class EventQueue
    {
        private:
            ALLEGRO_EVENT_QUEUE* _eventQueue;
            ALLEGRO_EVENT_SOURCE _eventSource;
            Dispatcher _dispatcher;
            SourceGroup _sources;

            EventBoy GetBoy();

        protected:
            void HandleEvent(const ALLEGRO_EVENT& event);
            void HandleEvent(ALLEGRO_EVENT_TYPE type);

        public:
            EventQueue(ALLEGRO_EVENT_QUEUE* queue, DispatchFilter filter);
            ~EventQueue();

            void ProcessNextEvent();
            bool Empty();

            void Register(ALLEGRO_EVENT_SOURCE* source);

            Dispatcher& GetDispatcher();

            template<typename T>
            void Register(T& client);
           
            template<typename T>
            void Register(T* client);

            template<typename T>
            inline EventBoy GetBoy(T& target);

            template<typename T>
            inline EventBoy GetBoy(T* target);
    };

    template<typename T>
    inline EventBoy EventQueue::GetBoy(T* target)
    {
        EventBoy boy = GetBoy();
        boy.ReBind(static_cast<ListenerHandle>(target));

        return boy;
    }

    template<typename T>
    inline EventBoy EventQueue::GetBoy(T& target)
    {
        EventBoy boy = GetBoy();
        boy.ReBind(static_cast<ListenerHandle>(&target));

        return boy;
    }

    template<typename T>
    void EventQueue::Register(T& client)
    {
        client.ConnectEvents(GetBoy(client));
    }

    template<typename T>
    void EventQueue::Register(T* client)
    {
        client->ConnectEvents(GetBoy(client));
    }
}

#endif
