#pragma once
#include <freeglut.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Misc.h"
#include "Texture.h"

#define MAXNAME 256
#define MAXTEXTURES 256 // 256 texture slots

// Texture coordinate macros
#define TOPRIGHT 1, 1
#define TOPLEFT 0, 1
#define BOTTOMLEFT 0, 0
#define BOTTOMRIGHT 1, 0

// mipmapping options
#define MIPMAP_LEVELS 3
#define MIPMAPS


typedef struct _tex
{
	GLubyte* image;

	GLuint ID;
	int width, height;
} Texture;

typedef enum _texname
{
	TEXTURE_GROUND = 0,
	TEXTURE_TROLL = 1,
	TEXTURE_KYS = 2,
	TEXTURE_FRING = 3,
	TEXTURE_JONADAM = 4,
	TEXTURE_ARMSTRONG = 5,
	TEXTURE_ROAD = 6,
	TEXTURE_COUNT
} TextureType;

static GLuint textureRegistry[MAXTEXTURES];

void init_textures(void);
GLuint load_texture_RGB(char*);
void texture_test(void);
void render_ground(void);
void bind_texture(TextureType);