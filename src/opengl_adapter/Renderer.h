#pragma once
#include "Window.h"
#include <iostream>

namespace LAM {
    class RendererBase {
    public:
        virtual void InitGLFW(int major_version, int minor_version) = 0;
        virtual void InitGLEW() = 0;

        void MakeContextCurrent(Window& w) {
            glfwMakeContextCurrent(w.handle);
        }

        virtual void SwapBuffers(Window&) = 0;

        template <class Callable = ActionFunc>
        void Render(Callable action) {
            if (isGlewInit() && isGlfwInit()) {
                action();
            }
        }

        virtual void SetClearColor(Color) = 0;

        void PollEvents() {
            glfwPollEvents();
        }

        virtual ~RendererBase() {
            glfwTerminate();
            _isGlfwInit = false;
        }

        inline static bool isGlfwInit() noexcept {
            return _isGlfwInit;
        }

        inline static bool isGlewInit() noexcept {
            return _isGlewInit;
        }

    protected:
        inline static void setGlfwInit(bool value) noexcept {
            _isGlfwInit = value;
        }
        inline static void setGlewInit(bool value) noexcept {
            _isGlewInit = value;
        }

    private:
        static bool _isGlfwInit;
        static bool _isGlewInit;
    };

    class OldRenderer final : public RendererBase {
    public:
        virtual void InitGLFW(int major_version = 2, int minor_version = 1) override;
        virtual void InitGLEW() override;
        virtual void SwapBuffers(Window&) override;
        virtual void SetClearColor(Color) override;

        ~OldRenderer() override {};
    };

    class MainRenderer final : public RendererBase {
    public:
        virtual void InitGLFW(int major_version = 3, int minor_version = 0) override;
        virtual void InitGLEW() override;
        virtual void SwapBuffers(Window&) override;
        virtual void SetClearColor(Color) override;

        ~MainRenderer() override {};
    };
}
