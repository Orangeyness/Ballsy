#ifndef H_UTIL_CONVERT_TO_STIRNG
#define H_UTIL_CONVERT_TO_STRING

#include <string>
#include <sstream>
#include <allegro5/allegro.h>

namespace Util
{
    template<typename T>
    class ConvertToString
    {
        public:
            static std::string Convert(const T& obj);
    };


    template<typename T>
    std::string ConvertToString<T>::Convert(const T& obj)
    {
        return obj.ToString();
    }

    template<>
    std::string ConvertToString<ALLEGRO_EVENT>::Convert(const ALLEGRO_EVENT& event);
}


#endif
