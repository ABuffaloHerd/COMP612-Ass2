#pragma once
#include <freeglut.h>
#include <stdio.h>
#include "Texture.h"
// Bad software design

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b);
void reset_material_properties(void);
void show_texture_registry(void);