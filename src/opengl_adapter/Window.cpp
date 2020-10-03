#include "Window.h"
#include <iostream>
#include <functional>

using namespace LAM;

void resize(GLFWwindow * _, int width, int height) {
    double ratio = width/static_cast<double>(height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1., 1., 1., -1.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Ctors.

Window::Window(Window&& window) noexcept {
    this->handle = window.handle;
    window.handle = nullptr;

    this->title = std::move(window.title);
}

Window::Window(const char* title, const Point& size, bool resizable, GLFWmonitor* monitor, Window* share) {
    this->master_ctor(title, size.x, size.y, resizable, monitor, share);
}

Window::Window(const char* title, Point&& size, bool resizable, GLFWmonitor* monitor, Window* share) {
    this->master_ctor(title, std::move(size.x), std::move(size.y), resizable, monitor, share);
}

Window::Window(std::string& title, const Point& size, bool resizable, GLFWmonitor* monitor, Window* share) {
    this->master_ctor(title.c_str(), size.x, size.y, resizable, monitor, share);
}

Window::Window(std::string& title, Point&& size, bool resizable, GLFWmonitor* monitor, Window* share) {
    this->master_ctor(title.c_str(), std::move(size.x), std::move(size.y), resizable, monitor, share);
}

void Window::master_ctor(const char* title, coord_t height, coord_t width, bool resizable, GLFWmonitor* monitor, Window* share) {
    this->handle = glfwCreateWindow(width, height, title, monitor, (share == nullptr ? nullptr : share->handle));

    if (!this->handle)
        throw WindowException("Failed to create a window.");

    glfwSetWindowCloseCallback(this->handle, [](GLFWwindow* w){ w = nullptr; });
    glfwSetWindowSizeCallback(this->handle, &resize);
    glfwWindowHint(GLFW_RESIZABLE, resizable);
}

// Dtor.
Window::~Window() {
    if (this->handle)
        glfwDestroyWindow(this->handle);
}


void Window::SetInput() {
    glfwSetInputMode(this->handle, GLFW_STICKY_KEYS, GL_TRUE);
}

LAM::KeyMode Window::PressedOrReleased(Keys key) const {
   return static_cast<KeyMode>(glfwGetKey(this->handle, static_cast<int>(key)));
}

bool Window::AboutToClose() const {
    if (this->handle)
        return glfwWindowShouldClose(this->handle);
    return true;
}

// Set title.
void Window::SetTitle(const std::string& title) {
    glfwSetWindowTitle(this->handle, title.c_str());
    this->title = title;
}

void Window::SetTitle(const char *title) {
    glfwSetWindowTitle(this->handle, title);
    this->title = std::string(title);
}

// Get title.
std::string Window::GetTitle() const {
    return this->title;
}

// Size manipulation.
void Window::SetSize(const Point& size) {
    glfwSetWindowSize(this->handle, size.x, size.y);
}

void Window::SetSize(Point&& size) {
    glfwSetWindowSize(this->handle, std::move(size.x), std::move(size.y));
}

void Window::SetSize(coord_t width, coord_t height) {
    glfwSetWindowSize(this->handle, width, height);
}

Window::Point Window::GetSize() const {
    Point res;
    glfwGetWindowSize(this->handle, &res.x, &res.y);
    return res;
}

// Screen position manipulation.
void Window::SetPos(const Point &new_pos) {
    glfwSetWindowPos(this->handle, new_pos.x, new_pos.y);
}

void Window::MoveBy(const Point &offset) {
    Point prev_pos;
    glfwGetWindowPos(this->handle, &prev_pos.x, &prev_pos.y);
    glfwSetWindowPos(this->handle, prev_pos.x + offset.x, prev_pos.y + offset.y);
}

Window::Point Window::GetPos() const {
    Point res;
    glfwGetWindowPos(this->handle, &res.x, &res.y);
    return res;
}

GLFWwindow* Window::GetHandle() {
    return this->handle;
}

void Window::Close() {
    if (this->handle) {
        glfwSetWindowShouldClose(this->handle, 1);
        this->handle = nullptr;
    }
}
