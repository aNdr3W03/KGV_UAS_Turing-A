#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Shape.h"

class Dodecagon : public Shape
{
    public:
        static unsigned int vertexArray;
        static unsigned int vertexBuffer;
        static unsigned int indexBuffer;

        Dodecagon();

        void draw();

    private:
        float vertices[52] = {
             0.0f,    0.0f,   0.5f,   0.5f,
             0.0f,    0.1f,   0.5f,   0.0f,
             0.5f,    0.866f, 0.75f,  0.067f,
             0.866f,  0.5f,   0.067f, 0.25f,
             1.0f,    0.0f,   1.0f,   0.5f,
             0.866f, -0.5f,   0.933f, 0.75f,
             0.5f,   -0.866f, 0.75f,  0.933f,
             0.0f,   -1.0f,   0.5f,   1.0f,
            -0.5f,   -0.866f, 0.25f,  0.933f,
            -0.866f, -0.5f,   0.067f, 0.75f,
            -1.0f,   -0.0f,   0.0f,   0.5f,
            -0.866f,  0.5f,   0.067f, 0.25f,
            -0.5f,    0.866f, 0.25f,  0.067f
        };

        unsigned int indexArr[36] = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 4, 5,
            0, 5, 6,
            0, 6, 7,
            0, 7, 8,
            0, 8, 9,
            0, 9, 10,
            0, 10, 11,
            0, 11, 12,
            0, 12, 1
        };
};
