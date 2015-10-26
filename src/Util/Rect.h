#ifndef H_UTIL_RECT
#define H_UTIL_RECT

#include "Util/Vector2.h"

#include <algorithm>

namespace Util
{
    class Rect
    {
        private:
            Vector2 _topLeft;
            Vector2 _bottomRight;

        public: 

            Rect() { }

            Rect(float x1, float y1, float x2, float y2)
            { 
                _topLeft.X = std::min(x1, x2);
                _topLeft.Y = std::min(y1, y2);

                _bottomRight.X = std::max(x1, x2);
                _bottomRight.Y = std::max(y1, y2);
            } 

            float Top() { return _topLeft.Y; }
            float Bottom() { return _bottomRight.Y; }
            float Left() { return _topLeft.X; }
            float Right() { return _bottomRight.X; }

            float Width() { return _bottomRight.X - _topLeft.X; }
            float Height() { return _bottomRight.Y - _topLeft.Y; }
    };

}


#endif
