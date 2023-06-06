#pragma once
#include <freeglut.h>
#include "GameObject.h"
#include "Misc.h"
#include <math.h>
#include "RenderList.h"

// enemy helicopter behaviour
typedef enum
{
	MOVE,
	SHOOT,
	IDLE
} AIState; // """""AI""""", not scripted

// Contains helicopter update and render functions
void render_helicopter(GameObject* this);

// enemy functions
// so that source.c can access it
void update_enemy_helicopter(GameObject* enemy);
void render_enemy_helicopter(GameObject* this);
void toggle_enemy(GameObject* enemy);