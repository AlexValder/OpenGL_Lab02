#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include <iostream>
#include <string>
#include <type_traits>
#include <memory>
#include <cassert>

namespace LAM {

    /**
     * Types
     */
    typedef void (*ActionFunc)();

    /**
     * Debug functions;
     */

    #ifndef NDEBUG
    inline void DebugPrint(const char* str) {
        std::cout << str << std::endl;
    }

    inline void DebugPrint(const std::string& str) {
        std::cout << str << std::endl;
    }
    #else
    void LAM::DebugPrint(const char*) {}
    void LAM::DebugPrint(const std::string&) {}
    #endif


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
    template <class T> //I recomend to add the floating point types support :-)
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
        T x, y;

        // Ctors.
        constexpr Vec2(T x = {}, T y = {}) : x(x), y(y) {}
        constexpr Vec2(const Vec2& vec) : x(vec.x), y(vec.y) {}
        constexpr Vec2(Vec2&& vec) noexcept : x(std::move(vec.x)), y(std::move(vec.y)) {}

        Vec2 operator*(int k) const noexcept {
            return Vec2(this->x * k, this->y * k);
        }

        T dot_product(const Vec2& vec) const noexcept {
            return this->x * vec.x + this->y * vec.y;
        }

        // These DO modify the object.
        Vec2& operator+=(const Vec2& vec) noexcept {
            this->x += vec.x;
            this->y += vec.y;
            return *this;
        }

        Vec2& operator-=(const Vec2& vec) noexcept {
            this->x -= vec.x;
            this->y -= vec.y;
            return *this;
        }

        Vec2& operator*=(double k) noexcept {
            this->x *= k;
            this->y *= k;
            return *this;
        }

        Vec2& operator=(const Vec2& vec) noexcept {
            this->x = vec.x;
            this->y = vec.y;
            return *this;
        }

        Vec2& operator=(Vec2&& vec) noexcept {
            this->x = std::move(vec.x);
            this->y = std::move(vec.y);
            return *this;
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
        return Vec2<T>(vec.x * k, vec.y * k);
    }

    template <class T>
    Vec2<T> operator*(double k, const Vec2<T>& vec) {
        return vec*k;
    }

    template <class T>
    Vec2<T> operator+(const Vec2<T>& vec1, const Vec2<T>& vec2) {
        return Vec2<T>(vec1.x + vec2.x, vec1.y + vec2.y);
    }

    template <class T>
    Vec2<T> operator-(const Vec2<T>& vec1, const Vec2<T>& vec2) {
        return Vec2<T>(vec1.x - vec2.x, vec1.y - vec2.y);
    }

    /**
     * Dot product, by a definition: A * B = a.x * b.x + a.y * b.y
     */
    template <class T>
    T dot_product(const Vec2<T>& vec1, const Vec2<T>& vec2) noexcept {
        return vec1.dot_product(vec2);
    }

    /**
     * Basic struct made to represent three-dimentional vector or a point.
     */
    template <class T = uint32_t,
              typename = typename std::enable_if<LAM::is_number<T>::value>>
    struct Vec3 {
        T x, y, z;

        constexpr Vec3(T x = {}, T y = {}, T z = {}) : x(x), y(y) {}
        constexpr Vec3(const Vec3& vec) : x(vec.x), y(vec.y) {}
        constexpr Vec3(Vec3&& vec) noexcept : x(std::move(vec.x)), y(std::move(vec.y)), z(std::move(vec.z)) {}

        Vec3 operator*(double k) const noexcept {
            return Vec3(this->x * k, this->y * k, this->z * k);
        }

        T dot_product(const Vec3& vec) const noexcept {
            return this->x * vec.x + this->y * vec.y + this->z * vec.z;
        }

        // These DO modify the object.
        Vec3& operator+=(const Vec3& vec) noexcept {
            this->x += vec.x;
            this->y += vec.y;
            this->z += vec.z;
            return *this;
        }

        Vec3& operator-=(const Vec3& vec) noexcept {
            this->x -= vec.x;
            this->y -= vec.y;
            this->z -= vec.z;
            return *this;
        }

        Vec3& operator*=(double k) noexcept {
            this->x *= k;
            this->y *= k;
            this->z *= k;
            return *this;
        }

        Vec3& operator=(const Vec3& vec) noexcept {
            this->x = vec.x;
            this->y = vec.y;
            this->z = vec.z;
            return *this;
        }

        Vec3& operator=(Vec3&& vec) noexcept {
            this->x = std::move(vec.x);
            this->y = std::move(vec.y);
            this->z = std::move(vec.z);
            return *this;
        }

        // Equality.
        bool operator==(const Vec3& vec) const noexcept { return (this->x == vec.x)&&(this->y == vec.y)&&(this->z == vec.z); }
        bool operator!=(const Vec3& vec) const noexcept { return !(*this == vec); }
    };

    /**
     * Dot product, by a definition: A * B = a.x * b.x + a.y * b.y + a.z * b.z
     */
    template <class T>
    T dot_product(const Vec3<T>& vec1, const Vec3<T>& vec2) noexcept {
        return vec1.dot_product(vec2);
    }


    struct Color final {
        float A, R, G, B;

        constexpr Color(uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t Alpha)
            : A(Alpha/256.f), R(Red/256.f), G(Green/256.f), B(Blue/256.f) {}

        Color(const glm::vec3&);
        Color(const glm::vec4&);

        operator glm::vec3() const;
        operator glm::vec4() const;

        static Color RandomColor();
        std::string toString() const;

        static const Color RED, GREEN, BLUE,
                            CYAN, MAGENTA, YELLOW,
                            LIGHTGRAY, TEAL, PURPLE, OLIVE,
                            BLACK, GRAY, WHITE;
    };

    enum GraphPrimitives : uint32_t {
        Points = GL_POINTS, // every vertice is a point
        Lines = GL_LINES, // every 2 vertices form a line
        Line_Strip = GL_LINE_STRIP, // lines connect the vertices
        Line_Loop = GL_LINE_LOOP, // lines connect the vertices and form a loop
        Triangles = GL_TRIANGLES, // every 3 vertices form a triangle
        Triangle_Strip = GL_TRIANGLE_STRIP, // every next triangle uses 2 vertices of a previous one
        Triangle_Fan = GL_TRIANGLE_FAN, // every next triangle uses the last one the previous one and the very first vertice
    };

    enum class Keys : int {
        Unknown = GLFW_KEY_UNKNOWN,
        Space = GLFW_KEY_SPACE,
        Apostrophe = GLFW_KEY_APOSTROPHE,
        Comma = GLFW_KEY_COMMA,
        Minus = GLFW_KEY_MINUS,
        Period = GLFW_KEY_PERIOD,
        Slash = GLFW_KEY_SLASH,
        Key0 = GLFW_KEY_0,
        Key1 = GLFW_KEY_1,
        Key2 = GLFW_KEY_2,
        Key3 = GLFW_KEY_3,
        Key4 = GLFW_KEY_4,
        Key5 = GLFW_KEY_5,
        Key6 = GLFW_KEY_6,
        Key7 = GLFW_KEY_7,
        Key8 = GLFW_KEY_8,
        Key9 = GLFW_KEY_9,
        Semicolon = GLFW_KEY_SEMICOLON,
        Equal = GLFW_KEY_EQUAL, /* = */
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
        LeftBracket = GLFW_KEY_LEFT_BRACKET, /* [ */
        Backslash = GLFW_KEY_BACKSLASH, /* \ */
        RightBracket = GLFW_KEY_RIGHT_BRACKET, /* [ */
        GraveAccent = GLFW_KEY_GRAVE_ACCENT, /* ` */
        World1 = GLFW_KEY_WORLD_1, /* non-US #1 */
        World2 = GLFW_KEY_WORLD_2, /* non-US #2 */
        Escape = GLFW_KEY_ESCAPE,
        Enter = GLFW_KEY_ENTER,
        Tab = GLFW_KEY_TAB,
        Backspace = GLFW_KEY_BACKSPACE,
        Insert = GLFW_KEY_INSERT,
        Delete = GLFW_KEY_DELETE,
        ArrowRight = GLFW_KEY_RIGHT,
        ArrowLeft = GLFW_KEY_LEFT,
        ArrowDown = GLFW_KEY_DOWN,
        ArrowUp = GLFW_KEY_UP,
        PageUp = GLFW_KEY_PAGE_UP,
        PageDown = GLFW_KEY_PAGE_DOWN,
        Home = GLFW_KEY_HOME,
        End = GLFW_KEY_END,
        CapsLock = GLFW_KEY_CAPS_LOCK,
        ScrollLock = GLFW_KEY_SCROLL_LOCK,
        NumLock = GLFW_KEY_NUM_LOCK,
        PrintScreen = GLFW_KEY_PRINT_SCREEN,
        Pause = GLFW_KEY_PAUSE,
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,
        F25 = GLFW_KEY_F25,
        KeyPad0 = GLFW_KEY_KP_0,
        KeyPad1 = GLFW_KEY_KP_1,
        KeyPad2 = GLFW_KEY_KP_2,
        KeyPad3 = GLFW_KEY_KP_3,
        KeyPad4 = GLFW_KEY_KP_4,
        KeyPad5 = GLFW_KEY_KP_5,
        KeyPad6 = GLFW_KEY_KP_6,
        KeyPad7 = GLFW_KEY_KP_7,
        KeyPad8 = GLFW_KEY_KP_8,
        KeyPad9 = GLFW_KEY_KP_9,
        KeyPadDecimal = GLFW_KEY_KP_DECIMAL,
        KeyPadDivide = GLFW_KEY_KP_DIVIDE,
        KeyPadMultiply = GLFW_KEY_KP_MULTIPLY,
        KeyPadSubstract = GLFW_KEY_KP_SUBTRACT,
        KeyPadAdd = GLFW_KEY_KP_ADD,
        KeyPadEnter = GLFW_KEY_KP_ENTER,
        KeyPadEqual = GLFW_KEY_KP_EQUAL,
        LeftShift = GLFW_KEY_LEFT_SHIFT,
        LeftControl = GLFW_KEY_LEFT_CONTROL,
        LeftAlt = GLFW_KEY_LEFT_ALT,
        LeftSuper = GLFW_KEY_LEFT_SUPER,
        RightShift = GLFW_KEY_RIGHT_SHIFT,
        RigthControl = GLFW_KEY_RIGHT_CONTROL,
        RightAlt = GLFW_KEY_RIGHT_ALT,
        RightSuper = GLFW_KEY_RIGHT_SUPER,
        Menu = GLFW_KEY_MENU,
        Last = GLFW_KEY_LAST
    };

    enum class KeyMode : int {
        Pressed = GLFW_PRESS,
        Released = GLFW_RELEASE
    };
}
