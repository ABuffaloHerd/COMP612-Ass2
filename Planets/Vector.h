#pragma once
#include <freeglut.h>

typedef struct _vec3
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Vector3;

typedef struct euler
{
	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;
} EulerAngle;