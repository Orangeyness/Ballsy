#include "EventFilters.h"

using namespace std::placeholders;

namespace Events
{
    intptr_t NoChildrenFilter()
    {
        return -1;
    }

    intptr_t EventTypeFilter(const ALLEGRO_EVENT& event)
    {
        return event.type;
    }

    intptr_t TimerSourceFilter(const ALLEGRO_EVENT& event)
    {
        return (intptr_t)event.timer.source;
    }

    intptr_t KeyCodeFilter(const ALLEGRO_EVENT& event)
    {
        return event.keyboard.keycode;
    }
}
