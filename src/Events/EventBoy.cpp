#include "Events/EventBoy.h"

namespace Events
{

    EventBoy::EventBoy(ListenerHandle listener, Dispatcher* dispatcher, SourceGroup* sources, ALLEGRO_EVENT_SOURCE* internalSource)
        :   _listener(listener),
            _dispatcher(dispatcher),
            _sources(sources),
            _internalSource(internalSource)
    { }

    EventBoy::EventBoy(Dispatcher* dispatcher, SourceGroup* sources, ALLEGRO_EVENT_SOURCE* internalSource)
        :   _listener(nullptr),
            _dispatcher(dispatcher),
            _sources(sources),
            _internalSource(internalSource)
    { }

    EventBoy::EventBoy()
        : _listener(nullptr)
    { }

    bool EventBoy::Enabled()
    {
        return _listener != nullptr;
    }

    void EventBoy::ReBind(ListenerHandle _handle)
    {
        _listener = _handle;
    }
    
    DispatcherProxy EventBoy::Listen()
    {
        return DispatcherProxy(_dispatcher, _listener);
    }

    DispatcherProxy EventBoy::Listen(intptr_t id)
    {
        return DispatcherProxy(&_dispatcher->Filter(id), _listener);
    }

    void EventBoy::StopListening()
    {
        DispatcherProxy(_dispatcher, _listener).StopAll();
    }

    void EventBoy::TalkFrom(ALLEGRO_EVENT_SOURCE* source)
    {
        _sources->AddSource(_listener, source);       
    }

    void EventBoy::StopTalking(ALLEGRO_EVENT_SOURCE* source)
    {
        _sources->RemoveSource(_listener, source);
    }

    void EventBoy::StopTalking()
    {
        _sources->RemoveSource(_listener);
    }

    void EventBoy::Talk(ALLEGRO_EVENT& event)
    {
        al_emit_user_event(_internalSource, &event, NULL);
    }

    void EventBoy::Talk(ALLEGRO_EVENT_TYPE type)
    {
        ALLEGRO_EVENT event;
        event.type = type;

        al_emit_user_event(_internalSource, &event, NULL);
    }
}
