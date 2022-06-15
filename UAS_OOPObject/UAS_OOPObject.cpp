// UAS_OOPObject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Util.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Square.h"
#include "Triangle.h"
#include "Dodecagon.h"

using namespace std;

float degToRad(float rotationDeg)
{
    return rotationDeg * 3.14159 / 180;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "UAS OOP Object - Turing A", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    
    Square s1;
    s1.setTranslation(0.0f, 0.7f, 0.0f);
    s1.setScale(0.2f, 0.2f, 1.0f);
    s1.setColor(0.5f, 0.8f, 1.0f, 1.0f);

    Triangle t1;
    t1.setTranslation(0.0f, -0.3f, 0.0f);
    t1.setScale(0.1f, 0.1f, 1.0f);
    t1.setColor(0.8f, 0.3f, 0.3f, 1.0f);

    Triangle t2;
    t2.setTranslation(0.4f, 0.0f, 0.0f);
    t2.setScale(0.3f, 0.3f, 1.0f);
    t2.setColor(0.8f, 0.8f, 0.3f, 1.0f);

    Dodecagon d1;
    d1.setTranslation(-0.4f, 0.0f, 0.0f);
    d1.setScale(0.1f, 0.1f, 1.0f);
    d1.setColor(0.8f, 0.0f, 0.8f, 1.0f);



    vector<Shape*> shapes;
    shapes.push_back(&s1);
    shapes.push_back(&t1);
    shapes.push_back(&t2);
    shapes.push_back(&d1);
    


    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);



    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);



    GLint uColor = glGetUniformLocation(program, "uColor");
    GLint uMat4x4 = glGetUniformLocation(program, "transformationMat4x4");

    Shape* shape;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        // Draw
        for (int i = 0; i < shapes.size(); i++)
        {
            shape = shapes.at(i);

            glUniform4fv(uColor, 1, &(shape->getColor()[0]));
            glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &(shape->getTransformationMat4x4()[0][0]));

            shapes.at(i)->draw();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
