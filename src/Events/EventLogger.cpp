#include "EventLogger.h"

using namespace std::placeholders;

namespace Events
{

    EventLogger::EventLogger(Util::Loggers::ILogger& logger)
        :   _logger(logger)
    { }

    void EventLogger::ConnectEvents(EventBoy e)
    {
        e  .Listen()
           .Do(std::bind(&EventLogger::OnEvent, this, _1));
    }

    void EventLogger::OnEvent(const ALLEGRO_EVENT& event)
    {
        _logger.Log(event);
    }

}
