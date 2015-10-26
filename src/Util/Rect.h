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

            float Top() const { return _topLeft.Y; }
            float Bottom() const { return _bottomRight.Y; }
            float Left() const { return _topLeft.X; }
            float Right() const { return _bottomRight.X; }

            float Width() const { return _bottomRight.X - _topLeft.X; }
            float Height() const { return _bottomRight.Y - _topLeft.Y; }

            bool Contains(Vector2 position) const
            {
                return  position.X >= Left() && 
                        position.X <= Right() && 
                        position.Y >= Top() &&
                        position.Y <= Bottom();
            }
    };

}


#endif
