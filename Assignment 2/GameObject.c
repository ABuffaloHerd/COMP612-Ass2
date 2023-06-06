#include "GameObject.h"

#define VELOCITY 90.0f * -1
extern const float FRAME_TIME_SEC;

GameObject* instantiate_missile(GLfloat pos[3]);
void update_missile(GameObject* missile);
void render_missile(GameObject* missile);

void update_bullet(GameObject* bullet);
void render_bullet(GameObject* bullet);

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
	m->isTimed = 1;

	printf("Fox 2!\n");
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

	if (missile->pos[1] <= 0)
	{
		play_sound(SOUND_EXPLODE);
		missile->timer = 0;
	}

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

// This indestructible bus will plough through anything it comes across. If only real buses could do that.
void update_bus(GameObject* bus)
{
	// Yeah, this thing moves at 10m/s 
	bus->pos[0] += 100 * FRAME_TIME_SEC;

	// This is a genuine magic number, i have no fucking clue why it's 5 or how that relates to the size of the ground plane. I just know it works.
	// So it turns out GROUNDSIZE is 5. huh.
	if(bus->pos[0] > GROUNDSIZE * 5)
		bus->pos[0] = -GROUNDSIZE * 5;
}

// this is one depressing object.
void render_bus(GameObject* bus)
{
	// auckland transport coloured bus
	GLfloat navyblue[] = { 0.00, 0.05, 0.530 , 1.0f };
	GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	reset_material_properties();

	// Goto bus position
	glPushMatrix();

		glTranslatef(bus->pos[0], bus->pos[1], bus->pos[2]);
		glRotatef(bus->rot[0], 1, 0, 0);
		glRotatef(bus->rot[1], 0, 1, 0);
		glRotatef(bus->rot[2], 0, 0, 1);

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, navyblue);
		glMaterialfv(GL_FRONT, GL_EMISSION, navyblue); // make it glow cause that's what copilot suggested

		// full model facelift
		glTranslatef(0.0f, 0.8f, 0.0f);

		// draw the bus
		// long rectangle
		glPushMatrix();

		// lift it up a bit
		glTranslatef(0.0f, 2.2f, 0.0f);
			glScalef(3.0f, 1.0f, 1.0f);
			glutSolidCube(4);
		glPopMatrix();

		// draw the wheels as two pathetic black cylinders

		// move to the side to draw the wheels
		glTranslatef(0.0f, 0.0f, -2.5f);
		// goto front wheels
		glPushMatrix();
			
			// move forward
			glTranslatef(3.0f, 0.0f, 0.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
			glMaterialfv(GL_FRONT, GL_EMISSION, black);
			glutSolidCylinder(0.8f, 5.0f, 10, 10);

		glPopMatrix();

		//// goto back wheels
		glPushMatrix();

			glTranslatef(-3.0f, 0.0f, 0.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
			glMaterialfv(GL_FRONT, GL_EMISSION, black);
			glutSolidCylinder(0.8f, 5.0f, 10, 10);

		glPopMatrix();
	
	glPopMatrix();
}

void random_heading(GLfloat heading[3])
{
	// Generate random numbers between -1 and 1
	GLfloat x = (GLfloat)rand() / (RAND_MAX / 2) - 1.0f;
	GLfloat y = (GLfloat)rand() / (RAND_MAX / 2) - 1.0f;
	GLfloat z = (GLfloat)rand() / (RAND_MAX / 2) - 1.0f;

	// Normalize the vector
	GLfloat len = sqrt(x * x + y * y + z * z);
	heading[0] = x / len;
	heading[1] = y / len;
	heading[2] = z / len;
}

GameObject* instantiate_bullet(GLfloat pos[3])
{
	GameObject* bullet = (GameObject*)malloc(sizeof(GameObject));
	bullet->pos[0] = pos[0];
	bullet->pos[1] = pos[1];
	bullet->pos[2] = pos[2];

	bullet->rot[0] = 0;
	bullet->rot[1] = 0;
	bullet->rot[2] = 0;

	bullet->isTimed = 1;
	bullet->timer = 5 * 120; // 5 seconds at 120fps

	bullet->update = update_bullet;
	bullet->render = render_bullet;

	random_heading(bullet->heading);

	return bullet;
}

#define BULLET_VELOCITY 60
void update_bullet(GameObject* bullet)
{
	bullet->pos[0] += bullet->heading[0] * BULLET_VELOCITY * FRAME_TIME_SEC;
	bullet->pos[1] += bullet->heading[1] * BULLET_VELOCITY * FRAME_TIME_SEC;
	bullet->pos[2] += bullet->heading[2] * BULLET_VELOCITY * FRAME_TIME_SEC;

	bullet->timer--;
}

void render_bullet(GameObject* bullet)
{
	// select materials
	reset_material_properties();
	GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat emm[] = { 0.5f, 0.0f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_EMISSION, emm);

	glPushMatrix();
	glTranslatef(bullet->pos[0], bullet->pos[1], bullet->pos[2]);
	glutSolidSphere(1, 10, 5);
	glPopMatrix();
}

void destroy_gameobject(GameObject* object)
{
	object->render = NULL;
	object->update = NULL;
}