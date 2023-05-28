#include "DisplayList.h"

DisplayList* init_displaylist(void)
{
	DisplayList* dlist = (DisplayList*)malloc(sizeof(DisplayList));
	dlist->list = 0;
	dlist->size = 0;
	return dlist;
}	

void insert_displaylist(DisplayList* target, void(*instructions)())
{
	if (target->size == 0)
	{
		target->list = (GLuint*)malloc(sizeof(GLuint));
	}
	else
	{
		target->list = (GLuint*)realloc(target->list, (target->size + 1) * sizeof(GLuint));
	}

	target->list[target->size] = glGenLists(1);
	glNewList(target->list[target->size], GL_COMPILE);
	instructions();
	glEndList();

	target->size++;
}

void render_displaylist(DisplayList* target)
{
	for (int i = 0; i < target->size; i++)
	{
		glCallList(target->list[i]);
	}
}	