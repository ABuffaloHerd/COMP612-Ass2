#include "GameObject.h"
#define VELOCITY 90.0f * -1
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


GameObject* instantiate_missile(GLfloat pos[3], GLfloat rot[3])
{
	GameObject* m = (GameObject*)malloc(sizeof(GameObject));

	m->pos[0] = pos[0];
	m->pos[1] = pos[1];
	m->pos[2] = pos[2];

	m->rot[0] = rot[0];
	m->rot[1] = rot[1];
	m->rot[2] = rot[2];

	m->update = update_missile;
	m->render = render_missile;

	m->timer = 2 * 120; // 5 seconds at 120fps

	printf("Fox 2!\n");
	printf("Missile %x: position: %f, %f, %f", m, m->pos[0], m->pos[1], m->pos[2]);
	printf("Supplied positions: %f, %f, %f", pos[0], pos[1], pos[2]);
	return m;
}

void update_missile(GameObject* missile)
{
	float dx = VELOCITY * FRAME_TIME_SEC * -cos(rad(missile->rot[1]));
	float dz = VELOCITY * FRAME_TIME_SEC * sin(rad(missile->rot[1]));

	missile->pos[0] += dx;
	missile->pos[1] -= 20.0f * FRAME_TIME_SEC;
	missile->pos[2] += dz;

	missile->timer--;

	//printf("Missile %x ", missile);
	//printf("Timer: %d, x: %d, z: %d\n", missile->timer, missile->pos[0], missile->pos[2]);
}

void render_missile(GameObject* missile)
{

	GLfloat yellow[] = {1.0f, 1.0f, 0.0f, 1.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_EMISSION, yellow);

	glPushMatrix();
	glTranslatef(missile->pos[0], missile->pos[1], missile->pos[2]);
	glRotatef(missile->rot[0], 1, 0, 0);
	glRotatef(missile->rot[1] - 90, 0, 1, 0);
	glRotatef(missile->rot[2], 0, 0, 1);
	glutSolidTeaspoon(3);

	glPopMatrix();

	reset_material_properties();
}

void destroy_gameobject(GameObject* object)
{
	object->render = NULL;
	object->update = NULL;
}