#ifndef H_EVENT_TYPES
#define H_EVENT_TYPES

#include <allegro5/allegro.h>
#include <string>

namespace Events
{

    #define CREATE_EVENT_TYPE(x) x,
    enum 
    {
        EVENT_USER_BASE = ALLEGRO_GET_EVENT_TYPE('R','L','B', 0),
        #include "Events/EventTypes.hpp"
    };
    #undef CREATE_EVENT_TYPE

    std::string GetUserEventTypeName(size_t EventType);
}
#endif
