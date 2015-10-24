#include "EventTypes.h"


namespace Events
{
    #define CREATE_EVENT_TYPE(x) #x,
    const char* UserEventTypeNames[] = {
        CREATE_EVENT_TYPE(EVENT_USER_BASE)
        #include "Events/EventTypes.hpp"
    };
    #undef CREATE_EVENT_TYPE

    std::string GetUserEventTypeName(size_t EventType)
    {
        return UserEventTypeNames[EventType - EVENT_USER_BASE];
    }
}
