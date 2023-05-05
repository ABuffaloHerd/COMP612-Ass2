#include "Object.h"

// render -> rotate ->translate
Model* new_object(void)
{
	Model* m = (Model*)malloc(sizeof(Model));

	m->pos[0] = 0;
	m->pos[1] = 0;
	m->pos[2] = 0;

	m->rot[0] = 0;
	m->rot[1] = 0;
	m->rot[2] = 0;
}