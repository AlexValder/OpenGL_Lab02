#pragma once
#include "Window.h"
#include <iostream>

namespace LAM {
    class RendererBase {
    public:
        virtual void InitGLFW(int major_version, int minor_version) = 0;
        virtual void InitGLEW() = 0;
        virtual void MakeContextCurrent(Window& w) { glfwMakeContextCurrent(w.handle); }
        virtual void SwapBuffers(Window&) = 0;
        virtual void RenderWindow(Window&) = 0;
        virtual void RenderTriangles(GLfloat vertices[], GLfloat colors[]) = 0;
        virtual void SetClearColor(Color) = 0;
        virtual void RenderVBO(GLuint VAO, GLenum TYPE, int size) = 0;
        void PollEvents() { glfwPollEvents(); }
        virtual ~RendererBase() {}
    };

    class MainRenderer : public RendererBase {
    public:

        void InitGLFW(int major_version = 2, int minor_version = 1) override {
            if(!glfwInit()) {
                std::cerr << "Failed to initialize GLFW" << std::endl;
                exit(-1);
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
        }

        void InitGLEW() override {
            glewExperimental = true;
            if(glewInit() != GLEW_OK) {
                std::cerr << "Failed to initialize GLEW" << std::endl;
                exit(-1);
            }
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

        void RenderVBO(GLuint VAO, GLenum TYPE, int size) override {
            glBindVertexArray(VAO);
            glEnableVertexAttribArray(0);
            glLineWidth(5);
            glDrawArrays(TYPE, 0, size);
            glDisableVertexAttribArray(0);
        }

        void SetClearColor(Color color) override {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(color.R, color.G, color.B, color.A/255.f);
        }

        ~MainRenderer() override {
            glfwTerminate();
        }
    };
}
