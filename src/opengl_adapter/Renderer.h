#pragma once
#include "Window.h"

namespace LAM {
    class RendererBase {
    public:
        virtual void Init() = 0;
        virtual void MakeContextCurrent(Window& w) { glfwMakeContextCurrent(w.handle); }
        virtual void SwapBuffers(Window&) = 0;
        virtual void RenderWindow(Window&) = 0;
        virtual void RenderTriangles(GLfloat vertices[], GLfloat colors[]) = 0;
        virtual void SetClearColor(Color) = 0;
        virtual void RenderVBO() = 0;
        void PollEvents() { glfwPollEvents(); }
        virtual ~RendererBase() {}
    };

    class MainRenderer : public RendererBase {
    public:

        void Init() override {
            glfwInit();

            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

            glewExperimental = true;
            glewInit();
        }

        void SwapBuffers(Window& w) override {
            glfwSwapBuffers(w.handle);
        }

        void RenderWindow(Window& w) override {
            this->SwapBuffers(w);
            this->PollEvents();
        }

        void RenderTriangles(GLfloat vertices[], GLfloat colors[]) override {
            ;
        }

        void RenderVBO() override {
            ;
        }

        void SetClearColor(Color color) override {
            glClearColor(color.R, color.G, color.B, color.A);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        ~MainRenderer() override {
            glfwTerminate();
        }
    };
}
