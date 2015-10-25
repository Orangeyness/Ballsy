#ifndef H_UTIL_VECTOR2
#define H_UTIL_VECTOR2

#include<string>
#include<algorithm>

namespace Util
{

    class Vector2
    {
        public:
            float X;
            float Y;

            Vector2() : X(0), Y(0) { }
            Vector2(float x, float y) : X(x), Y(y) { }

            friend Vector2 operator*(const Vector2& lhs, float rhs) { return Vector2(lhs.X * rhs, lhs.Y * rhs); }
            friend Vector2 operator/(const Vector2& lhs, float rhs) { return Vector2(lhs.X / rhs, lhs.Y / rhs); }
            friend Vector2 operator+(const Vector2& lhs, float rhs) { return Vector2(lhs.X + rhs, lhs.Y + rhs); }
            friend Vector2 operator-(const Vector2& lhs, float rhs) { return Vector2(lhs.X - rhs, lhs.Y - rhs); }

            friend Vector2 operator*(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.X * rhs.X, lhs.Y * rhs.Y); }
            friend Vector2 operator/(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.X / rhs.X, lhs.Y / rhs.Y); }
            friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.X + rhs.X, lhs.Y + rhs.Y); }
            friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2(lhs.X - rhs.X, lhs.Y - rhs.Y); }

            Vector2 operator~() { return Vector2(Y, X); }

            float Min() const { return std::min(X, Y); }
            float Max() const { return std::max(X, Y); }

            const std::string ToString() const { return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")"; }
    };

}

#endif
