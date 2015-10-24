#include "Util/ConvertToString.h"
#include "Events/EventTypes.h"

namespace Util
{
    template<>
    std::string ConvertToString<ALLEGRO_EVENT>::Convert(const ALLEGRO_EVENT& event)
    {
        std::stringstream ss;

        if (event.type >= Events::EVENT_USER_BASE)
        {
            ss << "Event |  USER   | Type: " << Events::GetUserEventTypeName(event.type);
        }
        else
        {
            ss << "Event | ALLEGRO | Type: " << event.type;
        }


        return ss.str();
    }
}
