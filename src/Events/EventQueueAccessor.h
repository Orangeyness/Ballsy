#ifndef H_EVENT_QUEUE_ACCESSOR
#define H_EVENT_QUEUE_ACCESSOR

#include "Events/EventCallBack.h"
#include "Events/EventTypes.h"

#include <allegro5/allegro.h>

class EventQueue;

class EventQueueAccessor
{
    friend EventQueue;

    private:
        EventQueue* _parent;
        ListenerHandle _target;

    protected:
        EventQueueAccessor(EventQueue* parent, ListenerHandle target);

    public: 
        void ListenFor(EventId eventId, EventCallBack callback);
        bool StopListeningFor(EventId eventId);
        bool StopListening();

        void TalkFrom(ALLEGRO_EVENT_SOURCE* source);
        bool StopTalkingFrom(ALLEGRO_EVENT_SOURCE* source);
        bool StopTalking();

        void Talk(ALLEGRO_EVENT& event);
};

#endif
