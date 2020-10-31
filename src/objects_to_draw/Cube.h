#pragma once

#include "../opengl_adapter/shared.h"
#include <array>

namespace LAM {
    namespace Cube {
        static constexpr std::array<float, 180> vertices = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f
        };

        static GLuint VAO, VBO;
        static constexpr GraphPrimitives TYPE = GraphPrimitives::Triangles;

        static void Init() {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(
              GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
              vertices.data(), GL_STATIC_DRAW
            );

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        static void Deinit() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }
    };
}
