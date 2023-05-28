#pragma once
#include <freeglut.h>
// Bad software design

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b) 
{
    GLfloat color[] = { r, g, b, 1.0f };  // Alpha is usually set to 1.0

    // Set the ambient and diffuse material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
}