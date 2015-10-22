#include "Events/EventLoop.h"
#include "Events/EventTypes.h"

#include <functional>

EventLoop::EventLoop()
    : EventQueue()
{
    _active = false;
    _renderNeeded = false;

    _renderEvent.user.type = EVENT_RENDER;

    RegisterListener(this);
}

EventLoop::~EventLoop()
{
    DeregisterListener(this);
}

void EventLoop::SetupListen(EventQueueAccessor eQ)
{
    eQ.ListenFor(GetEventId(EVENT_LOOP_RENDER_NEEDED), std::bind(&EventLoop::OnRenderNeeded, this));
    eQ.ListenFor(GetEventId(EVENT_LOOP_STOP), std::bind(&EventLoop::OnStop, this));
}

void EventLoop::OnRenderNeeded()
{
    _renderNeeded = true;
}

void EventLoop::OnStop()
{
    Stop();
}

void EventLoop::Run()
{
   _active = true;
   _renderNeeded = false;

   while(_active)
   {
       ProcessNextEvent();

       if (_renderNeeded && Empty())
       {
           _renderNeeded = false;
           BroadcastEvent(_renderEvent);
       }
   }
}

void EventLoop::Stop()
{
    _active = false;
}

