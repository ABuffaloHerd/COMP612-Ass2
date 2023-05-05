#pragma once
#include <freeglut.h>
#include <math.h>
#include <stdlib.h>

typedef struct _cam
{
	GLfloat looking[3];
	GLfloat pos[3];

	int lockon;
	GLfloat lockon_dist;
	GLfloat target_pos[3];

	void(*update)(struct _cam*);
} Camera;

Camera* new_camera(void);