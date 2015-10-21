#include "EventLoop.h"

#include "util/TracedException.h"

EventLoop::EventLoop()
    : _listenerMap()
{
    if (!al_is_system_installed())
        throw TracedException("Creating EventLoop before al_init");

    _eventQueue = al_create_event_queue();

    if (_eventQueue == nullptr)
        throw TracedException("Bad EventQueue");

    _active = false;
    _renderEvent.user.type = EventTypes::RENDER_EVENT;
}

EventLoop::~EventLoop()
{
    al_destroy_event_queue(_eventQueue);
}

void EventLoop::HandleEvent(const ALLEGRO_EVENT& event)
{
    auto listeners = _listenerMap.equal_range(event.type);
    for(auto it = listeners.first; it != listeners.second; ++it)
    {
        auto callback = it->second;
        auto result = callback(event);

        HandleCallbackResult(result);
    }
}

void EventLoop::HandleCallbackResult(EventCallbackResult result)
{
    switch(result)
    {
        case NORMAL:
            break;

        case NEED_RENDER:
            _renderNeeded = true;
            break;

        case STOP_LOOP:
            Stop();
            break;           
    }
}


void EventLoop::Run()
{
   _active = true;
   _renderNeeded = false;

   while(_active)
   {
        ALLEGRO_EVENT event;
        al_wait_for_event(_eventQueue, &event);

        HandleEvent(event);

        if (_renderNeeded && al_is_event_queue_empty(_eventQueue))
        {
            HandleEvent(_renderEvent);
            _renderNeeded = false;
        }
   }
}

void EventLoop::Stop()
{
    _active = false;
}

void EventLoop::RegisterSource(ALLEGRO_EVENT_SOURCE* source)
{
    al_register_event_source(_eventQueue, source);
}

void EventLoop::RegisterCallback(ALLEGRO_EVENT_TYPE eventType, EventCallback callback)
{
    _listenerMap.emplace(eventType, callback);
}

