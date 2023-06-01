#pragma once
// This file only contains headers for functions that draw static objects.
// It will be pushed into the display list in the main loop.

#include <stdlib.h>
#include "DisplayList.h"
#include "Texture.h"
#include <freeglut.h>
#include "Misc.h"
#include "GameObject.h"

void render_sun(void);
void render_gigantic_gus_fring(void);
GameObject* trollface_cylinder(GLfloat pos[3]);
