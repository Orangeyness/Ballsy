#include "EventListenerEntry.h"

EventListenerEntry::EventListenerEntry
    (ListenerHandle listener, EventId event, EventCallBack callBack)
    :   Listener(listener),
        Event(event),
        CallBack(callBack)
{ }
