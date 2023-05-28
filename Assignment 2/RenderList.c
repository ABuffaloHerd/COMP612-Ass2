#include "RenderList.h"

void renderlist_push(RenderList* list, GameObject* object)
{
	if (list->size == 0)
	{
		list->objects = (GameObject**)malloc(sizeof(GameObject*));
	}
	else
	{
		printf("Realloc!\n");
		list->objects = (GameObject**)realloc(list->objects, (list->size + 1) * sizeof(GameObject*));
	}

	list->objects[list->size] = object;
	list->size++;

	printf("size is now %d\n", list->size);
}

RenderList* renderlist_init(void)
{
	RenderList* list = (RenderList*)malloc(sizeof(RenderList));
	list->size = 0;
	list->objects = NULL;
	return list;
}

void renderlist_render(RenderList* list)
{
	for (unsigned int i = 0; i < list->size; i++)
	{
		GameObject* object = list->objects[i];
		if (object == NULL) continue;
		if (object->render != NULL)
		{
			object->render(object);
		}
	}
}

void renderlist_update(RenderList* list)
{
	// thanks mr gpt
	unsigned int i = 0;
	while (i < list->size)
	{
		GameObject* object = list->objects[i];
		if (object->update != NULL)
		{
			object->update(object);
		}

		if (object->timer == 0)
		{
			destroy_gameobject(object);
			free(object);

			// Remove the object from the list and shift the remaining objects down
			for (unsigned int j = i; j < list->size - 1; j++)
			{
				list->objects[j] = list->objects[j + 1];
			}

			// Reallocate the objects array to the new size
			list->size--;
			list->objects = realloc(list->objects, list->size * sizeof(GameObject*));

			printf("Destroyed object\n");
		}
		else
		{
			i++;
		}
	}
}