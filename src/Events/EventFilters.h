#ifndef H_EVENT_FILTERS
#define H_EVENT_FILTERS

#include <allegro5/allegro.h>
#include <functional>

using namespace std::placeholders;

namespace Events
{
    intptr_t NoChildrenFilter();
    intptr_t EventTypeFilter(const ALLEGRO_EVENT& event);
    intptr_t TimerSourceFilter(const ALLEGRO_EVENT& event);
    intptr_t KeyCodeFilter(const ALLEGRO_EVENT& event);

    typedef std::function<intptr_t(const ALLEGRO_EVENT&)> DispatchFilter;
}

#endif
