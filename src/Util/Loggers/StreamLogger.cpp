#include "Util/Loggers/StreamLogger.h"

namespace Util
{
    namespace Loggers
    {
        StreamLogger::StreamLogger(std::ostream& output)
            :   _output(output)
        { }

        void StreamLogger::Log(const std::string& message)
        {
            _output << message << std::endl;
        }
    }
}
