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
            AndroidLogger::Log(_name, message);
        }

        void AndroidLogger::Log(const std::string& name, const std::string& message)
        {
            __android_log_print(ANDROID_LOG_INFO, name.c_str(), "%s", message.c_str());
        }
    }
}

#endif
