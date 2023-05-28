#include "Misc.h"

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b)
{
    GLfloat color[] = { r, g, b, 1.0f };

    // Set the ambient and diffuse material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
}

void reset_material_properties(void) 
{
    GLfloat default_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f }; 
    GLfloat default_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
    GLfloat default_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    GLfloat default_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 
    GLfloat default_shininess = 100.0f; 

    glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, default_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, default_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, default_shininess);
}
