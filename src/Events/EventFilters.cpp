#include "EventFilters.h"

using namespace std::placeholders;

namespace Events
{
    namespace Filters
    {
        intptr_t NoChildren(const ALLEGRO_EVENT& event)
        {
            return -1;
        }

        intptr_t EventType(const ALLEGRO_EVENT& event)
        {
            return event.type;
        }

        intptr_t TimerSource(const ALLEGRO_EVENT& event)
        {
            return (intptr_t)event.timer.source;
        }

        intptr_t KeyCode(const ALLEGRO_EVENT& event)
        {
            return event.keyboard.keycode;
        }
    }
}
