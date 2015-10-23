#include "Events/EventLoop.h"
#include "Events/EventTypes.h"

#include <functional>

namespace Events
{

    EventLoop::EventLoop(ALLEGRO_EVENT_QUEUE* eventQueue, DispatchFilter filter)
        :   EventQueue(eventQueue, filter)
    {
        _active = false;
        _renderNeeded = false;

        _renderEvent.user.type = EVENT_RENDER;
    }

    EventLoop::~EventLoop()
    {
    }

    void EventLoop::ConnectEvents()
    {
        EventBoy boy = GetBoy(this);

        boy .Listen(EVENT_LOOP_RENDER_NEEDED)
            .Do(std::bind(&EventLoop::OnRenderNeeded, this));

        boy .Listen(EVENT_LOOP_STOP)
            .Do(std::bind(&EventLoop::OnStop, this));
    }

    void EventLoop::DisconnectEvents()
    {
        EventBoy boy = GetBoy(this);

        boy .Listen(EVENT_LOOP_RENDER_NEEDED).Stop();
        boy .Listen(EVENT_LOOP_STOP).Stop();
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

       ConnectEvents();

        while(_active)
        {
            ProcessNextEvent();

            if (_renderNeeded && Empty())
            {
                _renderNeeded = false;
                HandleEvent(_renderEvent);
            }
        }

        DisconnectEvents();
    }

    void EventLoop::Stop()
    {
        _active = false;
    }
}
