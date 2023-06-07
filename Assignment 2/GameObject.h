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

typedef enum
{
	RANDOM,
	AIMED,
	BOWP,
	TYPE_COUNT
} AttackType;

typedef struct _obj
{
	GLfloat pos[3];
	GLfloat rot[3];

	void(*render)(struct _obj*);
	void(*update)(struct _obj*);

	GLfloat velocity; // only used by cylinders and player helicopter

	// only used by bullet
	GLfloat heading[3];

	// used by bullets and missiles
	unsigned int timer;
	unsigned int isTimed;
} GameObject;

GameObject* new_gameobject(void(*render)(GameObject), void(*update)(GameObject*));
void destroy_gameobject(GameObject* object);

// Missile
GameObject* instantiate_missile(GLfloat pos[3], GLfloat rot[3]);

// Bus
void render_bus(GameObject* bus);
void update_bus(GameObject* bus);

// bullets
GameObject* instantiate_bullet(GLfloat pos[3], AttackType type);
GameObject* instantiate_bullet_given_heading(GLfloat pos[3], GLfloat heading[3]);