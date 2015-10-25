#include "Events/EventReader.h"
#include "Events/UserEvents/UserEvents.h"
#include "Util/TracedException.h"

namespace Events
{
    EventReader::EventReader(int eventType)
        :   _ownsPayLoad(true)
    { 
        _event.type = eventType;
        InternalSetPayLoad(0);
    }

    EventReader::EventReader(const ALLEGRO_EVENT& event)
        : _ownsPayLoad(false),
          _event(event)
    { }

    bool EventReader::IsOwner()
    {
        return _ownsPayLoad;
    }

    void EventReader::DisposePayLoad()
    {
        _event.user.data4 = 0;
    }

    bool EventReader::HasPayLoad()
    {
        return (InternalGetPayLoad() != 0);
    }

    bool EventReader::ShouldDisposePayLoad()
    {
        return (IsOwner() && HasPayLoad());
    }

    void EventReader::InternalSetPayLoad(intptr_t ptr)
    {
        if (!IsOwner())
            throw TracedException("Can't set payload we don't own");

        if (ShouldDisposePayLoad())
            DisposePayLoad();

        _event.user.data4 = ptr;
    }

    intptr_t EventReader::InternalGetPayLoad()
    {
        return _event.user.data4;
    }

    void EventReader::Transmit(ALLEGRO_EVENT_SOURCE* source)
    {
        if (!IsOwner())
            throw TracedException("Can't transmit Payload we don't own");

        al_emit_user_event(source, &_event, 0);

        _ownsPayLoad = false;
    }

    void EventReader::Dispose(const ALLEGRO_EVENT& event)
    {
        using namespace UserEvents;

        switch(event.type)
        {
            // Any user events which use dynamic allocation
            // need to have a case added here to ensure 
            // their payload is properly deallocated.
            // So make sure you've done that when you start
            // seeing them memory leaks.
            // Probably should put a case for every user event
            // you make.

            case RenderRegister::EventType:
                RenderRegister(event).DisposePayLoad();
                break;

            case RenderUnregister::EventType:
                RenderUnregister(event).DisposePayLoad();
                break;

            default:
                EventReader(event).DisposePayLoad();
                break;
        }
    }
}
