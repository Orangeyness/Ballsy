#ifdef ANDROID

#include "Util/Loggers/AndroidLogger.h"
#include <android/log.h>

namespace Util
{
    namespace Loggers
    {
        AndroidLogger::AndroidLogger(std::string name)
            :   _name(name)
        { }

        void AndroidLogger::Log(const std::string& message)
        {
            __android_log_print(ANDROID_LOG_INFO, _name.c_str(), "%s", message.c_str());
        }
    }
}

#endif
