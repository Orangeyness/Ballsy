#include "EventLoopListenerAdder.h"

EventLoopListenerAdder::EventLoopListenerAdder(EventLoop* parent)
    : _parent(parent)
{ }

void EventLoopListenerAdder::ListenFor(ALLEGRO_EVENT_TYPE eventType, EventCallback callback)
{
    _parent->RegisterCallback(eventType, callback);
}
