#pragma once
#include <freeglut.h>

typedef struct _cam
{
	GLfloat looking[3];
	GLfloat pos[3];
	GLfloat up[3];
} Camera;