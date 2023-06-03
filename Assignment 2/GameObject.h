#pragma once
#include <freeglut.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Texture.h"
#include "SoundSystem.h"
#include "Misc.h"
#include <math.h>
#include "Ground.h"

inline double rad(double deg)
{
	return deg * (3.14159 / 180.0);
}

typedef struct _obj
{
	char tag[256]; // 255 characters is plenty
	GLfloat pos[3];
	GLfloat rot[3];

	Texture* texture; // TODO: memory leak lol

	void(*render)(struct _obj*);
	void(*update)(struct _obj*);

	unsigned int timer;
	unsigned int isTimed;
} GameObject;

GameObject* new_gameobject(void(*render)(GameObject), void(*update)(GameObject*));
void destroy_gameobject(GameObject* object);

void render_cursor(GameObject*);

// Missile
GameObject* instantiate_missile(GLfloat pos[3], GLfloat rot[3]);

// Bus
void render_bus(GameObject* bus);
void update_bus(GameObject* bus);