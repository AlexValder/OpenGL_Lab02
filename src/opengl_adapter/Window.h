#ifndef WINDOW_H
#define WINDOW_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shared.h"
#include <map>

namespace LAM {

    struct WindowException : std::runtime_error {
        WindowException(const char* reason) noexcept : std::runtime_error(reason) {}
        const char* what() const noexcept override { return runtime_error::what(); }
        virtual ~WindowException() override {}
    };

    class Window {
    public:

        Window(const char* title, const Vec2<uint16_t>& size, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(const char* title, Vec2<uint16_t>&& size, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(std::string& title, const Vec2<uint16_t>& size, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(std::string& title, Vec2<uint16_t>&& size, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        virtual ~Window();

        void Open() const;
        void Close();

        void SetTitle(const std::string& title);
        std::string GetTitle() const;

        void SetInput();
        int IsPressed(int key);

        void Render();

        bool AboutToClose() const;

    private:
        GLFWwindow* handle;
        std::string title;

        void master_ctor(const char*, uint16_t, uint16_t, GLFWmonitor*, Window*);

        static std::map<GLFWwindow*, Window*> _windows;
        static void callback(GLFWwindow*);
    };
}

#endif // WINDOW_H
