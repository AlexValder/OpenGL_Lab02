#ifndef WINDOW_H
#include "Window.h"
#include <iostream>
#include <functional>

using namespace LAM;

std::map<GLFWwindow*, Window*> Window::_windows = {};

/// PUBLIC

// Ctors.
Window::Window(const char* title, const Point& size, GLFWmonitor* monitor, Window* share) {
    this->master_ctor(title, size.x, size.y, monitor, share);
}

Window::Window(const char* title, Point&& size, GLFWmonitor* monitor, Window* share) {
    this->master_ctor(title, std::move(size.x), std::move(size.y), monitor, share);
}

Window::Window(std::string& title, const Point& size, GLFWmonitor* monitor, Window* share) {
    this->master_ctor(title.c_str(), size.x, size.y, monitor, share);
}

Window::Window(std::string& title, Point&& size, GLFWmonitor* monitor, Window* share) {
    this->master_ctor(title.c_str(), std::move(size.x), std::move(size.y), monitor, share);
}

void Window::master_ctor(const char* title, coord_t height, coord_t width, GLFWmonitor* monitor, Window* share) {
    this->handle = glfwCreateWindow(width, height, title, monitor, (share == nullptr ? nullptr : share->handle));

    if (!this->handle)
        throw WindowException("Failed to create a window.");

    _windows.insert({this->handle, this});
    glfwSetWindowCloseCallback(this->handle, &Window::callback);
}

// Dtor.
Window::~Window() {
    if (this->handle)
        glfwDestroyWindow(this->handle);
}

// TODO
void Window::Open() const {
    glfwMakeContextCurrent(this->handle);
}
void Window::Close() {}

void Window::SetInput() {
    glfwSetInputMode(this->handle, GLFW_STICKY_KEYS, GL_TRUE);
}

int Window::IsPressed(int key) const {
    return glfwGetKey(this->handle, key);
}

void Window::Render() {
    glfwSwapBuffers(this->handle);
    glfwPollEvents();
}

bool Window::AboutToClose() const {
    if (this->handle)
        return !glfwWindowShouldClose(this->handle);
    else return false;
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

/// PRIVATE

void Window::callback(GLFWwindow* w) {
    if (_windows.find(w) != _windows.end()) {
       _windows[w]->handle = nullptr;
       _windows.erase(w);
    }
}

#endif // WINDOW_H
