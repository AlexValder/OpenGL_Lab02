#pragma once
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

        friend class RendererBase;
        friend class OldRenderer;
        friend class MainRenderer;

        using coord_t = int;
        using Point = Vec2<coord_t>;

        /*
         * Several overloaded constructors for different parameters, also a virtual destructor for potential
         * inheritance.
         */
        Window(const char* title, const Point& size, bool resizable = true, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(const char* title, Point&& size, bool resizable = true, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(std::string& title, const Point& size, bool resizable = true, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(std::string& title, Point&& size, bool resizable = true, GLFWmonitor* monitor = nullptr, Window* share = nullptr);

        Window(const Window& window) = delete;
        Window(Window&& window) noexcept;
        virtual ~Window();

        /*
         * Size manipulations.
         */
        Point GetSize() const;
        void SetSize(const Point& size);
        void SetSize(Point&& size);
        void SetSize(coord_t width, coord_t height);

        /*
         * Position manipulation.
         */
        void SetPos(const Point& new_pos);
        void MoveBy(const Point& offset);
        Point GetPos() const;

        /*
         * Title getter & setter.
         */
        void SetTitle(const std::string& title);
        void SetTitle(const char* title);
        std::string GetTitle() const;

        void SetInput();
        KeyMode PressedOrReleased(Keys key) const;
        void ToggleFullscreen();

        bool AboutToClose() const;
        void Close();

        GLFWwindow* GetHandle();
        GLFWmonitor* GetMonitor();

    private:
        GLFWwindow* handle;
        GLFWmonitor* monitor;
        std::string title;

        const Point _windowedSize;
        bool _fullscreen = false;

        void master_ctor(const char*, coord_t, coord_t, bool, GLFWmonitor*, Window*);
    };

}
