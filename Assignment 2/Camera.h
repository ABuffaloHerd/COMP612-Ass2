#pragma once
#include <freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _cam
{
	GLfloat pos[3]; // x, y, z
	GLfloat rot[3]; // a, b, g or pitch, yaw etc

	int locked;
	GLfloat dist;
	GLfloat lock_target[3];
	GLfloat lock_target_rot[3];

	void(*update)(struct _cam*);
	void(*set_target)(struct _cam*, GLfloat[3], GLfloat[3]);
} Camera;

// my name is proto your security is my motto
Camera* new_camera();