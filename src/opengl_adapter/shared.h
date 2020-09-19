#ifndef SHARED_H
#define SHARED_H

#include <string>
#include <type_traits>
#include <memory>

namespace LAM {

    /**
     * Dedicated namespace for constants of different types for
     * different purposes.
     */
    namespace Constants {
        static constexpr double PI = 3.141592653589793;
    }

    /**
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

    /**
     * Basic struct made to represent two-dimentional vector or a point.
     */
    template <class T = uint32_t,
              typename = typename std::enable_if<LAM::is_number<T>::value>>
    struct Vec2 {
        T x = {}, y = {};

        // Ctors.
        Vec2(T x, T y) : x(x), y(y) {}
        Vec2(const Vec2& vec) : x(vec.x), y(vec.y) {}
        Vec2(Vec2&& vec) noexcept : x(std::move(vec.x)), y(std::move(vec.y)) {}

        // These DO NOT modify the object.
        Vec2& operator+(const Vec2& vec) const noexcept { (this->x + vec.x, this->y + vec.y); }
        Vec2& operator-(const Vec2& vec) const noexcept { return Vec2(this->x - vec.x, this->y - vec.y); }

        //These DO modify the object.
        Vec2& operator+=(const Vec2& vec) noexcept {
            this->x += vec.x;
            this->y += vec.y;
            return this;
        }

        Vec2& operator-=(const Vec2& vec) noexcept {
            this->x -= vec.x;
            this->y -= vec.y;
            return this;
        }

        Vec2& operator*(int k) noexcept {
            this->x *= k;
            this->y *= k;
            return this;
        }

        Vec2& operator=(const Vec2& vec) noexcept {
            this->x = vec.x;
            this->y = vec.y;
            return this;
        }
        Vec2& operator=(Vec2&& vec) noexcept {
            this->x = std::move(vec.x);
            this->y = std::move(vec.y);
            return this;
        }

        // Equality.
        bool operator==(const Vec2& vec) const noexcept { return (this->x == vec.x)&&(this->y == vec.y); }
        bool operator!=(const Vec2& vec) const noexcept { return !(*this == vec); }
    };

    /**
      * Two overloads of multiplying a Vec2 by a scalar value (integer).
      */
    template <class T>
    Vec2<T> operator*(const Vec2<T>& vec, int k) {
        return Vec2(vec.x * k, vec.y * k);
    }

    template <class T>
    Vec2<T> operator*(int k, const Vec2<T>& vec) {
        return vec*k;
    }

    /**
     * Dot product, by a definition: A * B = a.x * b.x + a.y * b.y
     */
    template <class T>
    T dot_product(const Vec2<T>& vec1, const Vec2<T>& vec2) noexcept {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }
}

#endif // SHARED_H
