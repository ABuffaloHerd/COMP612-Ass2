#include "GameObject.h"

GameObject* new_gameobject(void(*render)(GameObject), void(*update)(GameObject*))
{
	GameObject* g = (GameObject*)malloc(sizeof(GameObject));

	g->pos[0] = 0;
	g->pos[1] = 0;
	g->pos[2] = 0;

	g->rot[0] = 0;
	g->rot[1] = 0;
	g->rot[2] = 0;

	g->render = render;
	g->update = update;

	return g;
}

void render_cursor(GameObject* this)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor4d(1.0, 0.0, 0.0, 1.0);
	glVertex3f(this->pos[0], this->pos[1], this->pos[2]);
	glVertex3f(this->pos[0] + 1, this->pos[1], this->pos[2]);

	glColor4d(0.0, 0.0, 1.0, 1.0);
	glVertex3f(this->pos[0], this->pos[1], this->pos[2]);
	glVertex3f(this->pos[0], this->pos[1] + 1, this->pos[2]);

	glColor4d(0.0, 1.0, 0.0, 1.0);
	glVertex3f(this->pos[0], this->pos[1], this->pos[2]);
	glVertex3f(this->pos[0], this->pos[1], this->pos[2] + 1);

	// one more line that represents the heading of the cursor on the xz plane
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glVertex3f(this->pos[0], this->pos[1], this->pos[2]);
	glVertex3f(this->pos[0] * cos(rad(this->rot[1])) * 1, this->pos[1], this->pos[2] * sin(rad(this->rot[1])) * 1);
	glEnd();
	glPopMatrix();
}