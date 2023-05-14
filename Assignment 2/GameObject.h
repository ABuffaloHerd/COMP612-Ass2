#pragma once
#include <freeglut.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Texture.h"

inline double rad(double deg)
{
	return deg * (3.14159 / 180.0);
}

typedef struct _obj
{
	GLfloat pos[3];
	GLfloat rot[3];

	Texture* texture;

	void(*render)(struct _obj*);
	void(*update)(struct _obj*);

	unsigned int timer;
} GameObject;

GameObject* new_gameobject(void(*render)(GameObject), void(*update)(GameObject*));
void render_cursor(GameObject*);