#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Shape.h"

class Star : public Shape
{
    public:
        static unsigned int vertexArray;
        static unsigned int vertexBuffer;
        static unsigned int indexBuffer;

        Star();

        void draw();

    private:
        float vertices[40] = {
              0.0f,    1.0f,   0.5f,    0.0f,
              0.233f,  0.3f,   0.6165f, 0.35f,
              0.95f,   0.3f,   0.975f,  0.35f,
              0.37f,  -0.11f,  0.185f,  0.555f,
              0.6f,   -0.8f,   0.8f,    0.9f,
              0.0f,   -0.375f, 0.5f,    0.6875f,
             -0.6f,   -0.8f,   0.2f,    0.9f,
             -0.37f,  -0.11f,  0.315f,  0.555f,
             -0.95f,   0.3f,   0.025f,  0.35f,
             -0.233f,  0.3f,   0.3835f, 0.35f
        };

        unsigned int indexArr[18] = {
            1, 6, 8,
            1, 6, 4,
            2, 3, 4,
            4, 5, 6,
            6, 7, 8,
            8, 9, 10
        };
};
