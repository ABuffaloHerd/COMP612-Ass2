#include <stdlib.h>
#include <freeglut.h>

typedef struct _dlist
{
	GLuint* list;
	unsigned int size;
} DisplayList;

DisplayList* init_displaylist(void);
void insert_displaylist(DisplayList* target, void(*instructions)());
void render_displaylist(DisplayList* target);