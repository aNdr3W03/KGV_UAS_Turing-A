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

float carMOV = 0.05f;
float carX   = 0.0f;
float carY   = 0.0f;

float currentTime = 0.0f;
float deltaTime   = 0.0f;
float lastTime    = 0.0f;
float timer       = 0.0f;

vector<Square>    sqr;
vector<Triangle>  tri;
vector<Dodecagon> dod;
vector<Star>      str;

float degToRad(float rotationDeg)
{
    return rotationDeg * 3.14159 / 180;
}

/* Input Handler */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Square    s;
    Triangle  t;
    Dodecagon d;
    Star      r;

    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_U)
        {
            if (carY < 0.3f) carY += carMOV;
            cout << "Car UP    = " << carY << "\n";
        }
        
        if (key == GLFW_KEY_J)
        {
            if (carY > -0.1f) carY -= carMOV;
            cout << "Car DOWN  = " << carY << "\n";
        }

        if (key == GLFW_KEY_H)
        {
            carX -= carMOV;
            if (carX <= -1.3f) carX = 1.3f;
            cout << "Car LEFT  = " << carX << "\n";
        }

        if (key == GLFW_KEY_K)
        {
            carX += carMOV;
            if (carX >= 1.3f) carX = -1.3f;
            cout << "Car RIGHT = " << carX << "\n";
        }

        /* Start of Car Movement */

        s = Square(); // Car Body (Bottom)
        s.setTranslation(0.0f + carX, -0.6f + carY, 0.0f);
        s.setScale(0.3f, 0.05f, 1.0f);
        s.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
        sqr[9] = s;

        s = Square(); // Car Body (Above)
        s.setTranslation(-0.03f + carX, -0.5f + carY, 0.0f);
        s.setScale(0.15f, 0.05f, 1.0f);
        s.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
        sqr[10] = s;

        t = Triangle(); // Car Body (Rear)
        t.setTranslation(-0.18f + carX, -0.5f + carY, 0.0f);
        t.setScale(0.05f, 0.05f, 1.0f);
        t.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
        tri[2] = t;

        t = Triangle(); // Car Body (Front)
        t.setTranslation(0.12f + carX, -0.5f + carY, 0.0f);
        t.setScale(0.05f, 0.05f, 1.0f);
        t.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
        tri[3] = t;



        s = Square(); // Car Window
        s.setTranslation(-0.03f + carX, -0.5f + carY, 0.0f);
        s.setScale(0.13f, 0.03f, 1.0f);
        s.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan
        sqr[11] = s;

        t = Triangle(); // Car Window (Rear)
        t.setTranslation(-0.16f + carX, -0.5f + carY, 0.0f);
        t.setScale(0.03f, 0.03f, 1.0f);
        t.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan
        tri[4] = t;

        t = Triangle(); // Car Window (Front)
        t.setTranslation(0.1f + carX, -0.5f + carY, 0.0f);
        t.setScale(0.03f, 0.03f, 1.0f);
        t.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan
        tri[5] = t;

        s = Square(); // Car Body (Window Divider)
        s.setTranslation(-0.03f + carX, -0.5f + carY, 0.0f);
        s.setScale(0.015f, 0.03f, 1.0f);
        s.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
        sqr[12] = s;



        d = Dodecagon(); // Rear Wheel
        d.setTranslation(-0.2f + carX, -0.65f + carY, 0.0f);
        d.setScale(0.05f, 0.05f, 1.0f);
        d.setColor(0.25f, 0.25f, 0.25f, 1.0f); // Black
        dod[1] = d;

        d = Dodecagon(); // Front Wheel
        d.setTranslation(0.2f + carX, -0.65f + carY, 0.0f);
        d.setScale(0.05f, 0.05f, 1.0f);
        d.setColor(0.25f, 0.25f, 0.25f, 1.0f); // Black
        dod[2] = d;

        d = Dodecagon(); // Rear Wheel Rim
        d.setTranslation(-0.2f + carX, -0.65f + carY, 0.0f);
        d.setScale(0.025f, 0.025f, 1.0f);
        d.setColor(0.75f, 0.75f, 0.75f, 1.0f); // Light Gray
        dod[3] = d;

        d = Dodecagon(); // Front Wheel Rim
        d.setTranslation(0.2f + carX, -0.65f + carY, 0.0f);
        d.setScale(0.025f, 0.025f, 1.0f);
        d.setColor(0.75f, 0.75f, 0.75f, 1.0f); // Light Gray
        dod[4] = d;

        /* End of Car Movement */
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

    /* GLFW Key Callback Input Handler */
    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    Square    s;
    Triangle  t;
    Dodecagon d;
    Star      r;

    /* Draw Grass, Road, and Stars */
    s = Square(); // Grass
    s.setTranslation(0.0f, -0.6f, 0.0f);
    s.setScale(1.0f, 0.4f, 1.0f);
    s.setColor(0.0f, 0.85f, 0.05f, 1.0f); // Green
    sqr.push_back(s); // sqr[0]

    s = Square(); // Road
    s.setTranslation(0.0f, -0.6f, 0.0f);
    s.setScale(1.0f, 0.3f, 1.0f);
    s.setColor(0.5f, 0.5f, 0.5f, 1.0f); // Gray
    sqr.push_back(s); // sqr[1]

    s = Square(); // Road Strip Top
    s.setTranslation(0.0f, -0.35f, 0.0f);
    s.setScale(1.0f, 0.01f, 1.0f);
    s.setColor(1.0f, 1.0f, 1.0f, 1.0f); // White
    sqr.push_back(s); // sqr[2]

    s = Square(); // Road Strip Bottom
    s.setTranslation(0.0f, -0.85f, 0.0f);
    s.setScale(1.0f, 0.01f, 1.0f);
    s.setColor(1.0f, 1.0f, 1.0f, 1.0f); // White
    sqr.push_back(s); // sqr[3]



    r = Star(); // Star
    r.setTranslation(-0.4f, 0.8f, 0.0f);
    r.setRotation(degToRad(20.0f), 0.0f, 0.0f, 1.0f);
    r.setScale(0.05f, 0.05f, 1.0f);
    r.setColor(1.0f, 0.8f, 0.0f, 1.0f); // Golden Yellow
    str.push_back(r); // str[0]

    r = Star(); // Star
    r.setTranslation(0.5f, 0.6f, 0.0f);
    r.setScale(0.02f, 0.02f, 1.0f);
    r.setColor(1.0f, 0.8f, 0.0f, 1.0f); // Golden Yellow
    str.push_back(r); // str[1]

    r = Star(); // Star
    r.setTranslation(0.7f, 0.7f, 0.0f);
    r.setRotation(degToRad(-10.0f), 0.0f, 0.0f, 1.0f);
    r.setScale(0.03f, 0.03f, 1.0f);
    r.setColor(1.0f, 0.8f, 0.0f, 1.0f); // Golden Yellow
    str.push_back(r); // str[2]
    /* Draw Grass, Road, and Stars */


    
    /* Draw Windmill */
    s = Square(); // Windmill Base
    s.setTranslation(-0.3f, -0.17f, 0.0f);
    s.setScale(0.12f, 0.03f, 0.0f);
    s.setColor(0.4f, 0.4f, 0.4f, 1.0f); // Dark Gray
    sqr.push_back(s); // sqr[4]

    s = Square(); // Windmill Tower
    s.setTranslation(-0.3f, 0.16f, 0.0f);
    s.setScale(0.02f, 0.3f, 0.0f);
    s.setColor(0.6f, 0.6f, 0.6f, 1.0f); // Gray
    sqr.push_back(s); // sqr[5]
    
    t = Triangle(); // Windmill Tower Left
    t.setTranslation(-0.32f, 0.16f, 0.0f);
    t.setScale(0.02f, 0.3f, 1.0f);
    t.setColor(0.6f, 0.6f, 0.6f, 1.0f); // Gray
    tri.push_back(t); // tri[0]

    t = Triangle(); // Windmill Tower Right
    t.setTranslation(-0.28f, 0.16f, 0.0f);
    t.setScale(0.02f, 0.3f, 1.0f);
    t.setColor(0.6f, 0.6f, 0.6f, 1.0f); // Gray
    tri.push_back(t); // tri[1]



    s = Square(); // Windmill Blade Top
    s.setTranslation(-0.3f, 0.46f, 0.0f);
    s.setRotation(degToRad(0), 0.0f, 0.0f, 1.0f);
    s.setTranslation(0.0f, 0.5f * 0.2f, 0.0f);
    s.setScale(0.04f, 0.5f, 1.0f);
    s.setColor(0.9f, 0.9f, 0.9f, 1.0f); // White Gray
    s.setScale(0.2f, 0.2f, 1.0f);
    sqr.push_back(s); // sqr[6]

    s = Square(); // Windmill Blade Right
    s.setTranslation(-0.3f, 0.46f, 0.0f);
    s.setRotation(degToRad(-120), 0.0f, 0.0f, 1.0f);
    s.setTranslation(0.0f, 0.5f * 0.2f, 0.0f);
    s.setScale(0.04f, 0.5f, 1.0f);
    s.setColor(0.9f, 0.9f, 0.9f, 1.0f); // White Gray
    s.setScale(0.2f, 0.2f, 1.0f);
    sqr.push_back(s); // sqr[7]

    s = Square(); // Windmill Blade Left
    s.setTranslation(-0.3f, 0.46f, 0.0f);
    s.setRotation(degToRad(-240), 0.0f, 0.0f, 1.0f);
    s.setTranslation(0.0f, 0.5f * 0.2f, 0.0f);
    s.setScale(0.04f, 0.5f, 1.0f);
    s.setColor(0.9f, 0.9f, 0.9f, 1.0f); // White Gray
    s.setScale(0.2f, 0.2f, 1.0f);
    sqr.push_back(s); // sqr[8]



    d = Dodecagon(); // Windmill Rotor
    d.setTranslation(-0.3f, 0.46f, 0.0f);
    d.setScale(0.035f, 0.035f, 1.0f);
    d.setColor(0.75f, 0.75f, 0.75f, 1.0f); // Light Gray
    dod.push_back(d); // dod[1]
    /* Draw Windmill */



    /* Draw Car */
    s = Square(); // Car Body (Bottom)
    s.setTranslation(0.0f, -0.6f, 0.0f);
    s.setScale(0.3f, 0.05f, 1.0f);
    s.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
    sqr.push_back(s); // sqr[9]

    s = Square(); // Car Body (Above)
    s.setTranslation(-0.03f, -0.5f, 0.0f);
    s.setScale(0.15f, 0.05f, 1.0f);
    s.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
    sqr.push_back(s); // sqr[10]

    t = Triangle(); // Car Body (Rear)
    t.setTranslation(-0.18f, -0.5f, 0.0f);
    t.setScale(0.05f, 0.05f, 1.0f);
    t.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
    tri.push_back(t); // tri[2]

    t = Triangle(); // Car Body (Front)
    t.setTranslation(0.12f, -0.5f, 0.0f);
    t.setScale(0.05f, 0.05f, 1.0f);
    t.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
    tri.push_back(t); // tri[3]



    s = Square(); // Car Window
    s.setTranslation(-0.03f, -0.5f, 0.0f);
    s.setScale(0.13f, 0.03f, 1.0f);
    s.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan
    sqr.push_back(s); // sqr[11]

    t = Triangle(); // Car Window (Rear)
    t.setTranslation(-0.16f, -0.5f, 0.0f);
    t.setScale(0.03f, 0.03f, 1.0f);
    t.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan
    tri.push_back(t); // tri[4]

    t = Triangle(); // Car Window (Front)
    t.setTranslation(0.1f, -0.5f, 0.0f);
    t.setScale(0.03f, 0.03f, 1.0f);
    t.setColor(0.5f, 1.0f, 1.0f, 1.0f); // Light Cyan
    tri.push_back(t); // tri[5]

    s = Square(); // Car Body (Window Divider)
    s.setTranslation(-0.03f, -0.5f, 0.0f);
    s.setScale(0.015f, 0.03f, 1.0f);
    s.setColor(0.9f, 0.1f, 0.0f, 1.0f); // Red
    sqr.push_back(s); // sqr[12]



    d = Dodecagon(); // Rear Wheel
    d.setTranslation(-0.2f, -0.65f, 0.0f);
    d.setScale(0.05f, 0.05f, 1.0f);
    d.setColor(0.25f, 0.25f, 0.25f, 1.0f); // Black
    dod.push_back(d); // dod[1]

    d = Dodecagon(); // Front Wheel
    d.setTranslation(0.2f, -0.65f, 0.0f);
    d.setScale(0.05f, 0.05f, 1.0f);
    d.setColor(0.25f, 0.25f, 0.25f, 1.0f); // Black
    dod.push_back(d); // dod[2]

    d = Dodecagon(); // Rear Wheel Rim
    d.setTranslation(-0.2f, -0.65f, 0.0f);
    d.setScale(0.025f, 0.025f, 1.0f);
    d.setColor(0.75f, 0.75f, 0.75f, 1.0f); // Light Gray
    dod.push_back(d); // dod[3]

    d = Dodecagon(); // Front Wheel Rim
    d.setTranslation(0.2f, -0.65f, 0.0f);
    d.setScale(0.025f, 0.025f, 1.0f);
    d.setColor(0.75f, 0.75f, 0.75f, 1.0f); // Light Gray
    dod.push_back(d); // dod[4]
    /* Draw Car */



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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.05f, 0.6f, 1.0f);

        glUseProgram(program);

        /* Draw here */
        for (int i = 0; i < sqr.size(); i++) // All Square
        {
            glUniform4fv(uColor, 1, &sqr[i].getColor()[0]);
            glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &sqr[i].getTransformationMat4x4()[0][0]);
            sqr[i].draw();
        }

        for (int i = 0; i < tri.size(); i++) // All Triangle
        {
            glUniform4fv(uColor, 1, &tri[i].getColor()[0]);
            glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &tri[i].getTransformationMat4x4()[0][0]);
            tri[i].draw();
        }

        /* Draw Windmill Blade Separate After The Windmill Tower Rendered */
        glUniform4fv(uColor, 1, &sqr[6].getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &sqr[6].getTransformationMat4x4()[0][0]);
        sqr[6].draw();

        glUniform4fv(uColor, 1, &sqr[7].getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &sqr[7].getTransformationMat4x4()[0][0]);
        sqr[7].draw();

        glUniform4fv(uColor, 1, &sqr[8].getColor()[0]);
        glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &sqr[8].getTransformationMat4x4()[0][0]);
        sqr[8].draw();
        /* Draw Windmill Blade Separate After The Windmill Tower Rendered */

        for (int i = 0; i < dod.size(); i++) // All Dodecagon
        {
            glUniform4fv(uColor, 1, &dod[i].getColor()[0]);
            glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &dod[i].getTransformationMat4x4()[0][0]);
            dod[i].draw();
        }

        for (int i = 0; i < str.size(); i++) // All Star
        {
            glUniform4fv(uColor, 1, &str[i].getColor()[0]);
            glUniformMatrix4fv(uMat4x4, 1, GL_FALSE, &str[i].getTransformationMat4x4()[0][0]);
            str[i].draw();
        }

        currentTime = glfwGetTime();
        deltaTime   = currentTime - lastTime;
        lastTime    = currentTime;

        if (glfwGetTime() - timer > 1.0)
        {
            timer += 0.1;

            s = Square(); // Windmill Blade Top
            s.setTranslation(-0.3f, 0.46f, 0.0f);
            s.setRotation(degToRad(-30 * timer), 0.0f, 0.0f, 1.0f);
            s.setTranslation(0.0f, 0.5f * 0.2f, 0.0f);
            s.setScale(0.04f, 0.5f, 1.0f);
            s.setColor(0.9f, 0.9f, 0.9f, 1.0f); // White Gray
            s.setScale(0.2f, 0.2f, 0.0f);
            sqr[6] = s;

            s = Square(); // Windmill Blade Right
            s.setTranslation(-0.3, 0.46f, 0.0f);
            s.setRotation(degToRad(-120 + (-30 * timer)), 0.0f, 0.0f, 1.0f);
            s.setTranslation(0.0f, 0.5f * 0.2f, 0.0f);
            s.setScale(0.04f, 0.5f, 1.0f);
            s.setColor(0.9f, 0.9f, 0.9f, 1.0f); // White Gray
            s.setScale(0.2f, 0.2f, 1.0f);
            sqr[7] = s;

            s = Square(); // Windmill Blade Left
            s.setTranslation(-0.3, 0.46f, 0.0f);
            s.setRotation(degToRad(-240 + (-30 * timer)), 0.0f, 0.0f, 1.0f);
            s.setTranslation(0.0f, 0.5f * 0.2f, 0.0f);
            s.setScale(0.04f, 0.5f, 1.0f);
            s.setColor(0.9f, 0.9f, 0.9f, 1.0f); // White Gray
            s.setScale(0.2f, 0.2f, 1.0f);
            sqr[8] = s;
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
