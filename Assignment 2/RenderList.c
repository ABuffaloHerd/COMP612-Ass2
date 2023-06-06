#include "RenderList.h"

void renderlist_push(RenderList* list, GameObject* object)
{
	if (list->size == 0)
	{
		list->objects = (GameObject**)malloc(sizeof(GameObject*));
	}
	else
	{
		list->objects = (GameObject**)realloc(list->objects, (list->size + 1) * sizeof(GameObject*));
	}

	list->objects[list->size] = object;
	list->size++;
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

		if (object->timer == 0 && object->isTimed)
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
		}
		else
		{
			i++;
		}
	}
}

GameObject* renderlist_find(char* tag, RenderList* list)
{
	printf("Renderlist FIND =================================D\n");
	for (int i = 0; i < list->size; i++)
	{
		GameObject* obj = list->objects[i];
		if (obj->tag[0] = '\0')
		{
			printf("Skipped find\n");
			continue;
		}
		if (strcmp(obj->tag, tag) == 0)
		{
			printf("Find found an object\n");
			return obj;
		}
	}
}