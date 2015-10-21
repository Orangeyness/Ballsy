#ifndef H_EVENT_LOOP_LISTENER_ADDER
#define H_EVENT_LOOP_LISTENER_ADDER

#include "EventLoop.h"

class EventLoopListenerAdder
{
    friend EventLoop;

    private:
        EventLoop* _parent;

    protected:
        EventLoopListenerAdder(EventLoop* parent);

    public: 
        void ListenFor(ALLEGRO_EVENT_TYPE eventType, EventCallback callback);
};


#endif
