#pragma once

#include "../opengl_adapter/shared.h"

namespace LAM {
    struct Cube {
        constexpr static float vertices[] = {
             -.5f, -.5f, -.5f,  .0f,  .0f,
              .5f, -.5f, -.5f,  1.f,  .0f,
              .5f,  .5f, -.5f,  1.f,  1.f,
              .5f,  .5f, -.5f,  1.f,  1.f,
             -.5f,  .5f, -.5f,  .0f,  1.f,
             -.5f, -.5f, -.5f,  .0f,  .0f,

             -.5f, -.5f,  .5f,  .0f,  .0f,
              .5f, -.5f,  .5f,  1.f,  .0f,
              .5f,  .5f,  .5f,  1.f,  1.f,
              .5f,  .5f,  .5f,  1.f,  1.f,
             -.5f,  .5f,  .5f,  .0f,  1.f,
             -.5f, -.5f,  .5f,  .0f,  .0f,

             -.5f,  .5f,  .5f,  1.f,  .0f,
             -.5f,  .5f, -.5f,  1.f,  1.f,
             -.5f, -.5f, -.5f,  .0f,  1.f,
             -.5f, -.5f, -.5f,  .0f,  1.f,
             -.5f, -.5f,  .5f,  .0f,  .0f,
             -.5f,  .5f,  .5f,  1.f,  .0f,

              .5f,  .5f,  .5f,  1.f,  .0f,
              .5f,  .5f, -.5f,  1.f,  1.f,
              .5f, -.5f, -.5f,  .0f,  1.f,
              .5f, -.5f, -.5f,  .0f,  1.f,
              .5f, -.5f,  .5f,  .0f,  .0f,
              .5f,  .5f,  .5f,  1.f,  .0f,

             -.5f, -.5f, -.5f,  .0f,  1.f,
              .5f, -.5f, -.5f,  1.f,  1.f,
              .5f, -.5f,  .5f,  1.f,  .0f,
              .5f, -.5f,  .5f,  1.f,  .0f,
             -.5f, -.5f,  .5f,  .0f,  .0f,
             -.5f, -.5f, -.5f,  .0f,  1.f,

             -.5f,  .5f, -.5f,  .0f,  1.f,
              .5f,  .5f, -.5f,  1.f,  1.f,
              .5f,  .5f,  .5f,  1.f,  .0f,
              .5f,  .5f,  .5f,  1.f,  .0f,
             -.5f,  .5f,  .5f,  .0f,  .0f,
             -.5f,  .5f, -.5f,  .0f,  1.f
         };

         static unsigned int VBO;

         static void Init() {

         }
    };
}
