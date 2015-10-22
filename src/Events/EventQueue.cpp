#include "EventQueue.h"

#include "Util/TracedException.h"

EventQueue::EventQueue()
    :   _callBackMap(),
        _listenerMap(),
        _sourceMap()
{
    if (!al_is_system_installed())
        throw TracedException("Creating EventQueue before al_init");

    _eventQueue = al_create_event_queue();

    if (_eventQueue == nullptr)
        throw TracedException("Bad EventQueue");

    al_init_user_event_source(&_eventSource);
    al_register_event_source(_eventQueue, &_eventSource);
}

EventQueue::~EventQueue()
{
    al_destroy_event_queue(_eventQueue);
    al_destroy_user_event_source(&_eventSource);
}

void EventQueue::HandleEvent(const ALLEGRO_EVENT& event)
{
    auto listeners = _callBackMap.equal_range(GetEventId(event));
    for(auto it = listeners.first; it != listeners.second; ++it)
    {
        auto callBack = it->second.CallBack;
        auto listener = it->second.Listener;

        callBack(event, GetAccessor(listener));
    }
}

bool EventQueue::DeregisterCallBack(ListenerHandle listener, EventId id)
{
    auto listeners = _callBackMap.equal_range(id);
    for(auto it = listeners.first; it != listeners.second; ++it)
    {
        ListenerHandle foundListener = it->second.Listener;

        if (foundListener == listener)
        {
            _callBackMap.erase(it);
            return true;
        }
    }

    return false;
}

void EventQueue::RegisterListener(EventListenerEntry entry)
{
    _callBackMap.emplace(entry.Event, entry);
    _listenerMap.emplace(entry.Listener, entry.Event);
}

bool EventQueue::DeregisterListener(ListenerHandle listener, EventId id)
{
    bool foundEventId = false;
    bool foundCallBack = false;

    auto eventIds = _listenerMap.equal_range(listener);
    for (auto it = eventIds.first; it != eventIds.second; ++it)
    {
        EventId foundId = it->second;
        if (foundId == id)
        {
            _listenerMap.erase(it);
            foundEventId = true;
            break;
        }
    }

    foundCallBack = DeregisterCallBack(listener, id);

    return foundEventId && foundCallBack;
}

bool EventQueue::DeregisterListener(ListenerHandle listener)
{
    bool missingCallBack = false;

    auto eventIds = _listenerMap.equal_range(listener);
    for (auto it = eventIds.first; it != eventIds.second; ++it)
    {
        EventId currentId = it->second;

        if (!DeregisterCallBack(listener, currentId))
            missingCallBack = true;
    }

    _listenerMap.erase(listener);

    return missingCallBack;
}

void EventQueue::RegisterEventSource(ListenerHandle listener, ALLEGRO_EVENT_SOURCE* source)
{
    _sourceMap.emplace(listener, source);
    al_register_event_source(_eventQueue, source);
}

bool EventQueue::DeregisterEventSource(ListenerHandle listener, ALLEGRO_EVENT_SOURCE* source)
{
    al_unregister_event_source(_eventQueue, source);

    auto sources = _sourceMap.equal_range(listener);
    for (auto it = sources.first; it != sources.second; ++it)
    {
        ALLEGRO_EVENT_SOURCE* foundSource = it->second;
        if (foundSource == source)
        {
            _sourceMap.erase(it);
            return true;
        }
    }

    return false;
}

bool EventQueue::DeregisterEventSource(ListenerHandle listener)
{
    auto sources = _sourceMap.equal_range(listener);
    for (auto it = sources.first; it != sources.second; ++it)
    {
        ALLEGRO_EVENT_SOURCE* foundSource = it->second;
        al_unregister_event_source(_eventQueue, foundSource);
    }

    _sourceMap.erase(sources.first, sources.second);

    return true;
}

void EventQueue::RegisterSource(ALLEGRO_EVENT_SOURCE* eventSource)
{
    al_register_event_source(_eventQueue, eventSource);
}

void EventQueue::BroadcastEvent(ALLEGRO_EVENT& userEvent)
{
    al_emit_user_event(&_eventSource, &userEvent, NULL);
}

void EventQueue::ProcessNextEvent()
{
    ALLEGRO_EVENT event;
    al_wait_for_event(_eventQueue, &event);

    HandleEvent(event);
}

bool EventQueue::Empty()
{
    return al_is_event_queue_empty(_eventQueue);
}
