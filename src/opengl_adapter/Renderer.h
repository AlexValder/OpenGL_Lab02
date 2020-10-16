#pragma once
#include "Window.h"
#include <iostream>

namespace LAM {
    class RendererBase {
    public:
        virtual void InitGLFW(int major_version, int minor_version) = 0;
        virtual void InitGLEW() = 0;
        void MakeContextCurrent(Window& w) { glfwMakeContextCurrent(w.handle); }
        virtual void SwapBuffers(Window&) = 0;
        virtual void RenderTriangles(GLfloat vertices[], GLfloat colors[]) = 0;
        virtual void SetClearColor(Color) = 0;
        virtual void RenderVBO(GLuint VAO, GLenum TYPE, int size) = 0;
        void PollEvents() { glfwPollEvents(); }
        virtual ~RendererBase() {}

        inline static bool isGlfwInit() noexcept;
        inline static bool isGlewInit() noexcept;

    protected:
        inline static void setGlfwInit(bool) noexcept;
        inline static void setGlewInit(bool) noexcept;

    private:
        static bool _isGlfwInit;
        static bool _isGlewInit;
    };

    class OldRenderer final : public RendererBase {
    public:
        virtual void InitGLFW(int major_version = 2, int minor_version = 1) override;
        virtual void InitGLEW() override;
        virtual void SwapBuffers(Window&) override;
        virtual void RenderTriangles(GLfloat*, GLfloat*) override;
        virtual void SetClearColor(Color) override;
        virtual void RenderVBO(GLuint VAO, GLenum TYPE, int size) override;

        ~OldRenderer() override;
    };
}
