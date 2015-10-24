#ifndef H_EVENTS_EVENT_LOGGER
#define H_EVENTS_EVENT_LOGGER

#include "Events/EventBoy.h"
#include "Util/Loggers/ILogger.h"

namespace Events
{
    class EventLogger
    {
        private: 
            Util::Loggers::ILogger& _logger;

        protected:
            void OnEvent(const ALLEGRO_EVENT& event);

        public:
            EventLogger(Util::Loggers::ILogger& logger);

            void ConnectEvents(EventBoy boy);
    };
}

#endif
