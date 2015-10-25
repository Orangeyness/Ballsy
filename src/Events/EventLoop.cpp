#include "Events/EventLoop.h"
#include "Events/EventTypes.h"
#include "Rendering/RenderQueue.h"

#include <functional>

using namespace Rendering;

namespace Events
{

    EventLoop::EventLoop(ALLEGRO_EVENT_QUEUE* eventQueue, DispatchFilter filter)
        :   EventQueue(eventQueue, filter)
    {
        _active = false;
    }

    EventLoop::~EventLoop()
    {
    }

    void EventLoop::ConnectEvents(EventBoy& boy)
    {
        boy .Listen(EVENT_LOOP_STOP)
            .Do(std::bind(&EventLoop::OnStop, this));

        boy .Register(_renderer);
    }

    void EventLoop::DisconnectEvents(EventBoy& boy)
    {
        boy .Listen(EVENT_LOOP_STOP).Stop();

        boy .Unregister(_renderer);
    }

    void EventLoop::OnStop()
    {
        _active = false;
    }

    void EventLoop::Run()
    {
        _active = true;

        Register(this);

        while(_active)
        {
            ProcessNextEvent();

            if (_renderer.NeedsRender())
                _renderer.Render();
        }

        Unregister(this);
    }
}
