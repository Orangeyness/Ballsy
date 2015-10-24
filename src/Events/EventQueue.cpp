#include "Events/EventQueue.h"

#include "Util/TracedException.h"

namespace Events
{
    EventQueue::EventQueue(ALLEGRO_EVENT_QUEUE* eventQueue, DispatchFilter filter)
        :   _eventQueue(eventQueue),
            _dispatcher(filter, true),
            _sources(eventQueue)
    {
        if (!al_is_system_installed())
            throw TracedException("Creating EventQueue before al_init");

        if (_eventQueue == nullptr)
            throw TracedException("Bad EventQueue");

        al_init_user_event_source(&_eventSource);
        al_register_event_source(_eventQueue, &_eventSource);
    }

    EventQueue::~EventQueue()
    {
        al_destroy_user_event_source(&_eventSource);
    }

    void EventQueue::Register(ALLEGRO_EVENT_SOURCE* source)
    {
        al_register_event_source(_eventQueue, source);
    }

    void EventQueue::ProcessNextEvent()
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(_eventQueue, &event);

        _dispatcher.FireEvent(event, GetBoy());
    }

    bool EventQueue::Empty()
    {
        return al_is_event_queue_empty(_eventQueue);
    }
    
    void EventQueue::HandleEvent(const ALLEGRO_EVENT& event)
    {
        _dispatcher.FireEvent(event, GetBoy());
    }

    void EventQueue::HandleEvent(ALLEGRO_EVENT_TYPE type)
    {
        ALLEGRO_EVENT event;
        event.type = type;

        _dispatcher.FireEvent(event, GetBoy());
    }

    Dispatcher& EventQueue::GetDispatcher()
    {
        return _dispatcher;
    }

    EventBoy EventQueue::GetBoy()
    {
        return EventBoy (&_dispatcher, &_sources, &_eventSource);
    }

}
