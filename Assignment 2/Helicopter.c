#include "Helicopter.h"

void render_helicopter(GameObject* this)
{
	glColor4d(0.8, 0.8, 0.8, 1.0);

	glPushMatrix();

	glTranslatef(this->pos[0], this->pos[1], this->pos[2]);

	glRotatef(this->rot[0], 1, 0, 0);
	glRotatef(this->rot[1], 0, 1, 0);
	glRotatef(this->rot[2], 0, 0, 1);

	glutSolidTeapot(2);

	glPopMatrix();
}

void update_helicopter(GameObject* this)
{
	this->rot[1] = modf(this->rot[1], 360);
}