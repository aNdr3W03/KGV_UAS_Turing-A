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
#include "Star.h"

using namespace std;

float carX = 0.0f;
float carY = 0.0f;

float degToRad(float rotationDeg)
{
    return rotationDeg * 3.14159 / 180;
}

// Input Handler
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        carY += 0.01f;
        cout << "Car Up = " << carY << "\n";
    }
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

    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    Square s1; // Grass
    s1.setTranslation(0.0f, -0.6f, 0.0f);
    s1.setScale(1.0f, 0.4f, 1.0f);
    s1.setColor(0.0f, 0.85f, 0.05f, 1.0f); // Green

    Square s2; // Road
    s2.setTranslation(0.0f, -0.6f, 0.0f);
    s2.setScale(1.0f, 0.3f, 1.0f);
    s2.setColor(0.5f, 0.5f, 0.5f, 1.0f); // Gray

    Square s3; // Road Strip Top
    s3.setTranslation(0.0f, -0.35f, 0.0f);
    s3.setScale(1.0f, 0.01f, 1.0f);
    s3.setColor(1.0f, 1.0f, 1.0f, 1.0f); // White

    Square s4; // Road Strip Bottom
    s4.setTranslation(0.0f, -0.85f, 0.0f);
    s4.setScale(1.0f, 0.01f, 1.0f);
    s4.setColor(1.0f, 1.0f, 1.0f, 1.0f); // White



    Square s5; // Car Body (Bottom)
    s5.setTranslation(0.0f, -0.6f, 0.0f);
    s5.setScale(0.3f, 0.05f, 1.0f);
    s5.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red

    Square s6; // Car Body (Above)
    s6.setTranslation(-0.03f, -0.5f, 0.0f);
    s6.setScale(0.15f, 0.05f, 1.0f);
    s6.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red

    Triangle t1; // Car Body (Rear)
    t1.setTranslation(-0.18f, -0.5f, 0.0f);
    t1.setScale(0.05f, 0.05f, 1.0f);
    t1.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red

    Triangle t2; // Car Body (Front)
    t2.setTranslation(0.12f, -0.5f, 0.0f);
    t2.setScale(0.05f, 0.05f, 1.0f);
    t2.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red



    Square s7; // Car Window
    s7.setTranslation(-0.03f, -0.5f, 0.0f);
    s7.setScale(0.13f, 0.03f, 1.0f);
    s7.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan

    Triangle t3; // Car Window (Rear)
    t3.setTranslation(-0.16f, -0.5f, 0.0f);
    t3.setScale(0.03f, 0.03f, 1.0f);
    t3.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan

    Triangle t4; // Car Window (Front)
    t4.setTranslation(0.1f, -0.5f, 0.0f);
    t4.setScale(0.03f, 0.03f, 1.0f);
    t4.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan

    Square s8; // Car Body (Window Divider)
    s8.setTranslation(-0.03f, -0.5f, 0.0f);
    s8.setScale(0.015f, 0.03f, 1.0f);
    s8.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red



    Dodecagon d1; // Rear Wheel
    d1.setTranslation(-0.2f, -0.65f, 0.0f);
    d1.setScale(0.05f, 0.05f, 1.0f);
    d1.setColor(0.25f, 0.25f, 0.25f, 1.0f); // Black

    Dodecagon d2; // Front Wheel
    d2.setTranslation(0.2f, -0.65f, 0.0f);
    d2.setScale(0.05f, 0.05f, 1.0f);
    d2.setColor(0.25f, 0.25f, 0.25f, 1.0f); // Black

    Dodecagon d3; // Rear Wheel Rim
    d3.setTranslation(-0.2f, -0.65f, 0.0f);
    d3.setScale(0.025f, 0.025f, 1.0f);
    d3.setColor(0.75f, 0.75f, 0.75f, 1.0f); // Light Gray
    
    Dodecagon d4; // Front Wheel Rim
    d4.setTranslation(0.2f, -0.65f, 0.0f);
    d4.setScale(0.025f, 0.025f, 1.0f);
    d4.setColor(0.75f, 0.75f, 0.75f, 1.0f); // Light Gray



    Star r1; // Bintang
    r1.setTranslation(-0.4f, 0.8f, 0.0f);
    r1.setRotation(degToRad(20.0f), 0.0f, 0.0f, 1.0f);
    r1.setScale(0.05f, 0.05f, 1.0f);
    r1.setColor(1.0f, 0.8f, 0.0f, 1.0f);

    Star r2; // Bintang
    r2.setTranslation(0.5f, 0.6f, 0.0f);
    r2.setScale(0.02f, 0.02f, 1.0f);
    r2.setColor(1.0f, 0.8f, 0.0f, 1.0f);

    Star r3; // Bintang
    r3.setTranslation(0.7f, 0.7f, 0.0f);
    r3.setRotation(degToRad(-10.0f), 0.0f, 0.0f, 1.0f);
    r3.setScale(0.03f, 0.03f, 1.0f);
    r3.setColor(1.0f, 0.8f, 0.0f, 1.0f);



    vector<Shape*> shapes;
    shapes.push_back(&s1);
    shapes.push_back(&s2);
    shapes.push_back(&s3);
    shapes.push_back(&s4);

    shapes.push_back(&s5);
    shapes.push_back(&s6);
    shapes.push_back(&t1);
    shapes.push_back(&t2);

    shapes.push_back(&s7);
    shapes.push_back(&t3);
    shapes.push_back(&t4);
    shapes.push_back(&s8);

    shapes.push_back(&d1);
    shapes.push_back(&d2);
    shapes.push_back(&d3);
    shapes.push_back(&d4);

    shapes.push_back(&r1);
    shapes.push_back(&r2);
    shapes.push_back(&r3);



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
        glClearColor(0.0f, 0.05f, 0.6f, 1.0f);

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
