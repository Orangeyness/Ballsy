#ifndef H_EVENTS_EVENT_CALL_BACK
#define H_EVENTS_EVENT_CALL_BACK

#include <allegro5/allegro.h>
#include <functional>

namespace Events
{

    class EventBoy;

    typedef std::function<void(const ALLEGRO_EVENT&, EventBoy&)> EventCallBack;

}

#endif
