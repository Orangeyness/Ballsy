#ifndef H_UTIL_LOGGERS_ILOGGER
#define H_UTIL_LOGGERS_ILOGGER

#include "Util/ConvertToString.h"

#include <allegro5/allegro.h>
#include <string>

namespace Util
{
    namespace Loggers
    {
        class ILogger
        {
            public:
                virtual void Log(const std::string& message) = 0;

                template<typename T>
                void Log(const T& object);

        };

        template<typename T>
        void ILogger::Log(const T& object)
        {
            Log(ConvertToString<T>::Convert(object));
        }
    }
}

#endif
