#ifndef H_EVENT_LISTENER_ENTRY
#define H_EVENT_LISTENER_ENTRY

#include "Events/EventCallBack.h"
#include "Events/EventTypes.h"

class EventListenerEntry
{
    friend class EventQueue;

    public:
        EventListenerEntry(ListenerHandle listener, EventId event, EventCallBack callBack);

    protected:
        ListenerHandle Listener;
        EventId Event;
        EventCallBack CallBack;
};

#endif
