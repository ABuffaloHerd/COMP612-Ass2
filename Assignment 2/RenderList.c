#include "RenderList.h"

void renderlist_push(RenderList* list, GameObject* object)
{
	if (list->size == 0)
	{
		list->objects = (GameObject*)malloc(sizeof(GameObject));
	}
	else
	{
		list->objects = (GameObject*)realloc(list->objects, list->size + 1);
	}

	list->objects[list->size] = *object;
}