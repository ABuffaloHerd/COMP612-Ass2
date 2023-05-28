#pragma once
#include "GameObject.h"
#include <stdlib.h>

typedef struct _rlist
{
	GameObject* objects;
	unsigned int size;
} RenderList;

// TODO: List of objects or list of object pointers?
void renderlist_push(RenderList* list, GameObject object);

