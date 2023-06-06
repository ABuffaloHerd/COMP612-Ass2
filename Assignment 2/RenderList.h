#pragma once
#include "GameObject.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _rlist
{
	GameObject** objects; // array of object pointers
	unsigned int size;
} RenderList;

// TODO: List of objects or list of object pointers?
void renderlist_push(RenderList* list, GameObject* object);
void renderlist_render(RenderList* list);
void renderlist_update(RenderList* list);
RenderList* renderlist_init(void);
GameObject* renderlist_find(char* tag, RenderList* list);
