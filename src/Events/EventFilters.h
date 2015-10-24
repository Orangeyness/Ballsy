#ifndef H_EVENT_FILTERS
#define H_EVENT_FILTERS

#include <allegro5/allegro.h>
#include <functional>

using namespace std::placeholders;

namespace Events
{
    namespace Filters
    {
        intptr_t NoChildren(const ALLEGRO_EVENT& event);
        intptr_t EventType(const ALLEGRO_EVENT& event);
        intptr_t KeyCode(const ALLEGRO_EVENT& event);

        intptr_t TimerSource(const ALLEGRO_EVENT& event);
        intptr_t DisplaySource(const ALLEGRO_EVENT& event);
    }

    typedef std::function<intptr_t(const ALLEGRO_EVENT&)> DispatchFilter;
}

#endif
