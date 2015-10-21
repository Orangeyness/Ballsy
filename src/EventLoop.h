#ifndef H_EVENT_LOOP
#define H_EVENT_LOOP

#include <allegro5/allegro.h>
#include <unordered_map>
#include <functional>

class EventLoopListenerAdder;

enum EventCallbackResult
{
    NORMAL,
    NEED_RENDER,
    STOP_LOOP,
};

typedef std::function<EventCallbackResult(const ALLEGRO_EVENT&)> EventCallback;

class EventLoop
{
    friend EventLoopListenerAdder;

    private:
        ALLEGRO_EVENT_QUEUE* _eventQueue;
        ALLEGRO_EVENT _renderEvent;
        std::unordered_multimap<ALLEGRO_EVENT_TYPE, EventCallback> _listenerMap;
        bool _active;
        bool _renderNeeded;

        void HandleEvent(const ALLEGRO_EVENT& event);
        void HandleCallbackResult(EventCallbackResult result);

    protected:
        void RegisterCallback(ALLEGRO_EVENT_TYPE eventType, EventCallback callback);

    public:
        EventLoop();
        ~EventLoop();

        void Run();
        void Stop();

        template<typename T>
        void Register(T& eventActor);

        template<typename T>
        void RegisterListener(T& eventLister);

        template<typename T>
        void RegisterSource(T& eventSource);

        void RegisterSource(ALLEGRO_EVENT_SOURCE* source);
};

template<typename T>
void EventLoop::Register(T& eventActor)
{
    RegisterSource(eventActor);
    RegisterListener(eventActor);
}

template<typename T>
void EventLoop::RegisterSource(T& eventSource)
{
    al_register_event_source(_eventQueue, eventSource.GetEventSource());
}

template<typename T>
void EventLoop::RegisterListener(T& eventListener)
{
    eventListener.SetEventLoop(EventLoopListenerAdder(this));
}

#include "EventTypes.h"
#include "EventLoopListenerAdder.h"
#endif
