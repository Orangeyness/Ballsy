#ifndef H_UTIL_LOGGERS_STREAM_LOGGER
#define H_UTIL_LOGGERS_STREAM_LOGGER

#include "Util/Loggers/ILogger.h"
#include <ostream>

namespace Util
{
    namespace Loggers
    {

        class StreamLogger : public ILogger
        {
            private:
                std::ostream& _output;

            public:
                StreamLogger(std::ostream& output);
                
                virtual void Log(const std::string& message) override;
        };

    }
}

#endif
