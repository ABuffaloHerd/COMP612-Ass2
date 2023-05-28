#include "GameObject.h"

extern const float FRAME_TIME_SEC;

void update_missile(GameObject* missile);
void render_missile(GameObject* missile);
GameObject* instantiate_missile(GLfloat pos[3]);

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


GameObject* instantiate_missile(GLfloat pos[3])
{
	GameObject* m = (GameObject*)malloc(sizeof(GameObject));

	m->pos[0] = pos[0];
	m->pos[1] = pos[1];
	m->pos[2] = pos[2];

	m->update = update_missile;
	m->render = render_missile;
}

void update_missile(GameObject* missile)
{
	static float vel = 10.0f;
	// calculate forward vector
	float dx = vel * FRAME_TIME_SEC * cos(rad(missile->rot[1]));
	float dz = vel * FRAME_TIME_SEC * -sin(rad(missile->rot[1]));

	missile->pos[0] += dx;
	missile->pos[2] += dz;
}

void render_missile(GameObject* missile)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(missile->pos[0], missile->pos[1], missile->pos[2]);
	glutSolidTeaspoon(1.0);

	glPopMatrix();
}