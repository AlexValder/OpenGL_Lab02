#include "RenderObject.h"
using namespace LAM;

RenderObject::RenderObject(std::vector<GLfloat>& data)
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(float), _data.data(), GL_STATIC_DRAW);

//    auto stride = (_tex_dim + _dim) * sizeof(float);

//    glVertexAttribPointer(0, _dim, GL_FLOAT, false, stride, (void*)0);
//    glEnableVertexAttribArray(0);

//    glVertexAttribPointer(1, _tex_dim, GL_FLOAT, false, stride, (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
}
