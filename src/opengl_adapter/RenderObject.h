#pragma once
#include "shared.h"
#include <vector>

namespace LAM {
    class RenderObject final {
    public:
        RenderObject(std::vector<GLfloat>& data);
    private:
        std::vector<GLfloat> _data;
        GLuint _VAO;
        GLuint _VBO;
    };
}
