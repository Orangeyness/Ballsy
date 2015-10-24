#ifdef ANDROID

#ifndef H_UTIL_LOGGERS_ANDROID_LOGGER
#define H_UTIL_LOGGERS_ANDROID_LOGGER

#include "Util/Loggers/ILogger.h"
#include <string>

namespace Util
{
    namespace Loggers
    {
        class AndroidLogger : public ILogger
        {
            private:
                std::string _name;

            public:
                AndroidLogger(std::string name);
                virtual void Log(const std::string& message) override;
                static void Log(const std::string& name, const std::string& message);
        };
    }
}
#endif
#endif
