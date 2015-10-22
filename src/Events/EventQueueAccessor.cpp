#include "Events/EventQueueAccessor.h"
#include "Events/EventQueue.h"

EventQueueAccessor::EventQueueAccessor(EventQueue* parent, ListenerHandle target)
    :   _parent(parent),
        _target(target)
{ }

void EventQueueAccessor::ListenFor(EventId eventId, EventCallBack callBack)
{
    _parent->RegisterListener(EventListenerEntry(_target, eventId, callBack));
}

bool EventQueueAccessor::StopListeningFor(EventId eventId)
{
    return _parent->DeregisterListener(_target, eventId);
}

bool EventQueueAccessor::StopListening()
{
    return _parent->DeregisterListener(_target);
}

void EventQueueAccessor::TalkFrom(ALLEGRO_EVENT_SOURCE* source)
{
    _parent->RegisterEventSource(_target, source);
}

bool EventQueueAccessor::StopTalkingFrom(ALLEGRO_EVENT_SOURCE* source)
{
    return _parent->DeregisterEventSource(_target, source);
}

bool EventQueueAccessor::StopTalking()
{
    return _parent->DeregisterEventSource(_target);
}

void EventQueueAccessor::Talk(ALLEGRO_EVENT& event)
{
    return _parent->BroadcastEvent(event);
}
