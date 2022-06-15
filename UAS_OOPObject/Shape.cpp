#include "Shape.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Shape::draw()
{
    
}

void Shape::setColor(glm::vec4 newColor)
{
    color = glm::vec4(newColor);
}

void Shape::setColor(float red, float green, float blue, float alpha)
{
    setColor(glm::vec4(red, green, blue, alpha));
}

glm::vec4 Shape::getColor()
{
    return color;
}

glm::mat4x4 Shape::getTransformationMat4x4()
{
    return transformationMat4x4;
}

void Shape::setTranslation(glm::vec3 newTranslation)
{
    transformationMat4x4 = glm::translate(transformationMat4x4, newTranslation);
}

void Shape::setTranslation(float transX, float transY, float transZ)
{
    setTranslation(glm::vec3(transX, transY, transZ));
}

void Shape::setRotation(float angle, glm::vec3 axis)
{
    transformationMat4x4 = glm::rotate(transformationMat4x4, angle, axis);
}

void Shape::setScale(glm::vec3 newSclae)
{
    transformationMat4x4 = glm::scale(transformationMat4x4, newSclae);
}

void Shape::setScale(float scaleX, float scaleY, float scaleZ)
{
    setScale(glm::vec3(scaleX, scaleY, scaleZ));
}
