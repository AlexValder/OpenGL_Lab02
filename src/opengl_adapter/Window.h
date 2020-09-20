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

        using coord_t = int;
        using Point = Vec2<coord_t>;

        /*
         * Several overloaded constructors for different parameters, also a virtual destructor for potential
         * inheritance.
         */
        Window(const char* title, const Point& size, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(const char* title, Point&& size, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(std::string& title, const Point& size, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        Window(std::string& title, Point&& size, GLFWmonitor* monitor = nullptr, Window* share = nullptr);
        virtual ~Window();


        /*
         * TODO: open & close function. (Do we need them?)
         */
        void Open() const;
        void Close();

        /*
         * Size manipulations.
         */
        Point GetSize() const;
        void SetSize(const Point& size);
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
        int IsPressed(int key) const;

        /*
         * Call this every frame.
         */
        void Render();

        bool AboutToClose() const;

    private:
        GLFWwindow* handle;
        std::string title;

        void master_ctor(const char*, coord_t, coord_t, GLFWmonitor*, Window*);

        static std::map<GLFWwindow*, Window*> _windows;
        static void callback(GLFWwindow*);
    };
}
