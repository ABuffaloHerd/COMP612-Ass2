#pragma once
#include <freeglut.h>

// render -> rotate ->translate handled by display function. Render only uses glut library to place object in world
typedef struct _model
{
	GLfloat pos[3];
	GLfloat rot[3];

	void(*update)(struct _model*); // update model (rotate, translate etc)
	void(*render)(struct _model*);
} Model;

