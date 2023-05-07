#pragma once
#include <freeglut.h>
#include <stdlib.h>

inline double rad(double deg)
{
	return deg * (3.14159 / 180.0);
}

typedef struct _obj
{
	GLfloat pos[3];
	GLfloat rot[3];

	void(*render)(struct _obj*);
	void(*update)(struct _obj*);
} GameObject;

GameObject* new_gameobject(void(*render)(GameObject), void(*update)(GameObject*));
void render_cursor(GameObject*);