#ifndef H_EVENT_TYPES
#define H_EVENT_TYPES

#include <allegro5/allegro.h>

typedef unsigned long EventId;

const ALLEGRO_EVENT_TYPE EVENT_BASE                     = ALLEGRO_GET_EVENT_TYPE('R','L','B', 0);
const ALLEGRO_EVENT_TYPE EVENT_RENDER                   = EVENT_BASE + 0;
const ALLEGRO_EVENT_TYPE EVENT_LOOP_RENDER_NEEDED       = EVENT_BASE + 1;
const ALLEGRO_EVENT_TYPE EVENT_LOOP_STOP                = EVENT_BASE + 2;

const ALLEGRO_EVENT_TYPE EVENT_SCENE_PAUSE              = EVENT_BASE + 3;
const ALLEGRO_EVENT_TYPE EVENT_SCENE_RESUME             = EVENT_BASE + 4;

namespace 
{
    inline EventId internalGetEventId(ALLEGRO_EVENT_TYPE eventType, int mod)
    {
        return ((EventId)eventType) | (mod << sizeof(ALLEGRO_EVENT_TYPE));
    }
}

inline EventId GetEventId(ALLEGRO_EVENT_TYPE eventType)
{
    return ((EventId)eventType);
}

inline EventId GetTimerEventId(ALLEGRO_EVENT_TYPE eventType, ALLEGRO_TIMER* timer)
{
    // SO HACK
    // Event Id clearly needs to be a stuct of something.
    return eventType ^ (long)timer;
}

inline EventId GetKeyboardEventId(ALLEGRO_EVENT_TYPE eventType, int keyCode)
{
    return internalGetEventId(eventType, keyCode);
}

inline EventId GetEventId(const ALLEGRO_EVENT& event)
{
    switch(event.type)
    {
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_KEY_UP:
        case ALLEGRO_EVENT_KEY_CHAR:
            return GetKeyboardEventId(event.type, event.keyboard.keycode);

        case ALLEGRO_EVENT_TIMER:
            return GetTimerEventId(event.type, event.timer.source);
    }

    return GetEventId(event.type);
}

#endif
