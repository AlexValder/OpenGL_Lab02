#ifndef SHARED_H
#define SHARED_H

#include <string>
#include <type_traits>
#include <typeinfo>

namespace LAM {

    /*
     * Dedicated namespace for constants of different types for
     * different purposes.
     */
    namespace Constants {
        static constexpr double PI = 3.141592653589793;
    }

    /*
     * Template constraint to only include integers and floating-point
     * types, both signed and unsigned. Explicitly excludes chars.
     */
    template <class T>
    struct is_number : std::integral_constant<bool,
                        std::is_arithmetic<T>::value &&
                        !(std::is_same<char, T>::value ||
                          std::is_same<char16_t, T>::value ||
                          std::is_same<char32_t, T>::value ||
                          std::is_same<wchar_t, T>::value ||
                          std::is_same<unsigned char, T>::value ||
                          std::is_same<signed char, T>::value)>{};

    /*
     * Basic struct made to represent two-dimentional vector or a point.
     */
    template <typename T = uint32_t,
              typename = typename std::enable_if<LAM::is_number<T>::value>>
    struct Vec2 {
        T x = {}, y = {};

        Vec2(T x, T y) : x(x), y(y) {}
        Vec2(const Vec2& vec) : x(vec.x), y(vec.y) {}
        Vec2(Vec2&& vec) : x(std::move(vec.x)), y(std::move(vec.y)) {}

        Vec2 operator+(const Vec2& vec) { return Vec2(this->x + vec.x, this->y + vec.y); }
        Vec2 operator-(const Vec2& vec) { return Vec2(this->x - vec.x, this->y - vec.y); }
        Vec2& operator=(const Vec2& vec) {
            this->x = vec.x;
            this->y = vec.y;
            return this;
        }
        Vec2& operator=(Vec2&& vec) {
            this->x = std::move(vec.x);
            this->y = std::move(vec.y);
            return this;
        }
        bool operator==(const Vec2& vec) { return (this->x == vec.x)&&(this->y == vec.y); }
        bool operator!=(const Vec2& vec) { return (this->x != vec.x)||(this->y != vec.y); }
    };
}

#endif // SHARED_H
