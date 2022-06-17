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
              0.0f,    1.0f,   
              0.233f,  0.3f,   
              0.95f,   0.3f,   
              0.37f,  -0.11f,  
              0.6f,   -0.8f,   
              0.0f,   -0.375f, 
             -0.6f,   -0.8f,   
             -0.37f,  -0.11f,  
             -0.95f,   0.3f,   
             -0.233f,  0.3f,   
        };

        unsigned int indexArr[36] = {
            
        };
};
