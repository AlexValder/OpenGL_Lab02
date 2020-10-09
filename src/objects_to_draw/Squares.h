#pragma once

#include "../opengl_adapter/shared.h"

namespace LAM {
    namespace Squares {
        GLfloat vertices[] = {
             0.,  0.,  0.,
             1.,  0.,  0.,
             1.,  1.,  0.,
             0.,  1.,  0.,

             0.,  0.,  0.,
             0.,  1.,  0.,
            -1.,  1.,  0.,
            -1.,  0.,  0.
        };

        GLfloat colors[] = {
            255, 0, 0,
            255, 0, 0,
            255, 0, 0,
            255, 0, 0,

            0, 0, 255,
            0, 0, 255,
            0, 0, 255,
            0, 0, 255
        };
    }
}
