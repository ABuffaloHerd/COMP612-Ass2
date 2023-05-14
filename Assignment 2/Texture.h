#pragma once
#include <freeglut.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAXNAME 256

typedef struct _tex
{
	char filename[MAXNAME]; // TODO: is this needed?
	char shortname[MAXNAME]; // for linkedlist
	GLubyte* image;

	GLuint ID;
	int width, height;
} Texture;

Texture* load_texture(char*, char*);

void texture_test(Texture*);