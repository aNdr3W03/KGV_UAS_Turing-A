#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Shape.h"

class Triangle : public Shape
{
    public:
        static unsigned int vertexArray;
        static unsigned int vertexBuffer;
        static unsigned int indexBuffer;

        Triangle();

        void draw();

    private:
        float vertices[12] = {
             0.0f,  1.0f, 0.5f, 0.0f,
            -1.0f, -1.0f, 0.0f, 1.0f,
             1.0f, -1.0f, 1.0f, 1.0f
        };

        unsigned int indexArr[3] = {
            0, 1, 2
        };
};
