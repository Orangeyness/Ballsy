#ifndef H_UTIL_TRACED_EXCEPTION
#define H_UTIL_TRACED_EXCEPTION

#include <exception>
#include <stdexcept>
#include <sstream>

namespace Util
{
    class TracedException : public std::runtime_error
    {
        private:
            std::string _what;
            std::string _fileName;
            int _lineNumber;


        public:
            explicit TracedException(const std::string& what, const std::string& file, int line)
                : std::runtime_error(what)
            {
                _fileName = file;
                _lineNumber = line;

                std::stringstream whatBuilder;
                whatBuilder << "At " << origin() << ", " << std::runtime_error::what();
                _what = whatBuilder.str();
            }

            virtual const char* what() const noexcept
            {
                return _what.c_str();
            }

            virtual std::string origin() const noexcept
            {
                std::stringstream stringBuilder;
                stringBuilder << _fileName << ":" << _lineNumber;

                return stringBuilder.str();
            }
    };
}

#define TracedException(x) \
    Util::TracedException(x, __FILE__, __LINE__)

#endif
