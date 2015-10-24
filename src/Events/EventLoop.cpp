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
        _renderAllowed = true;
    }

    EventLoop::~EventLoop()
    {
    }

    void EventLoop::ConnectEvents()
    {
        EventBoy boy = GetBoy(this);

        boy .Listen(EVENT_LOOP_STOP)
            .Do(std::bind(&EventLoop::OnStop, this));

        boy .Listen(EVENT_RENDER_NEEDED)
            .Do(std::bind(&EventLoop::OnRenderNeeded, this));

        boy .Listen(EVENT_RENDER_NOT_ALLOWED)
            .Do(std::bind(&EventLoop::OnRenderAllowedChanged, this, false));

        boy .Listen(EVENT_RENDER_ALLOWED)
            .Do(std::bind(&EventLoop::OnRenderAllowedChanged, this, true));
    }

    void EventLoop::DisconnectEvents()
    {
        EventBoy boy = GetBoy(this);

        boy .Listen(EVENT_LOOP_STOP).Stop();
        boy .Listen(EVENT_RENDER_NEEDED).Stop();
        boy .Listen(EVENT_RENDER_NOT_ALLOWED).Stop();
        boy .Listen(EVENT_RENDER_ALLOWED).Stop();
    }

    void EventLoop::OnRenderAllowedChanged(bool state)
    {
        _renderAllowed = state;
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

            if (_renderAllowed && _renderNeeded && Empty())
            {
                _renderNeeded = false;
                HandleEvent(EVENT_RENDER);
            }
        }

        DisconnectEvents();
    }

    void EventLoop::Stop()
    {
        _active = false;
    }
}
