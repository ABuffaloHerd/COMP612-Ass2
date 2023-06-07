#include "GameObject.h"

#define VELOCITY 90.0f * -1
extern const float FRAME_TIME_SEC;
extern GameObject* copter;

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

		// light
		glPushMatrix();

			GLfloat pos[] = { 6.0f, 0.6f, 2.5f, 1.0f };
			glLightfv(GL_LIGHT2, GL_POSITION, pos);

			// set the colours
			GLfloat colour[] = { 0.6, 0.6, 0.0, 1.0 };
			glLightfv(GL_LIGHT2, GL_DIFFUSE, colour);
			glLightfv(GL_LIGHT2, GL_SPECULAR, colour);

			// set some properties
			GLfloat down[] = { 1.0f, -0.3f, 0.0f };
			glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0f);
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, down);
			glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0f);
		
		glPopMatrix();

		// The light object so that we can actually see it
		glPushMatrix();

		GLfloat pissyellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pissyellow);
		glMaterialfv(GL_FRONT, GL_EMISSION, pissyellow);

		glTranslatef(6.0f, 0.6f, 2.5f);
		glRotatef(90, 0, 1, 0);
		glutSolidCylinder(0.4, 0.4, 29, 5);

		glPopMatrix();
	
	glPopMatrix();
}

void aimed_heading(GLfloat here[3], GLfloat there[3], GLfloat out[3])
{
	out[0] = there[0] - here[0];
	out[1] = there[1] - here[1];
	out[2] = there[2] - here[2];

	// normalize
	GLfloat len = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);
	out[0] /= len;
	out[1] /= len;
	out[2] /= len;
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

GameObject* instantiate_bullet(GLfloat pos[3], AttackType type)
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

	if (type == AIMED)
	{
		aimed_heading(bullet->pos, copter->pos, bullet->heading);
	}
	else random_heading(bullet->heading);

	return bullet;
}

GameObject* instantiate_bullet_given_heading(GLfloat pos[3], GLfloat heading[3])
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
	
	bullet->heading[0] = heading[0];
	bullet->heading[1] = heading[1];
	bullet->heading[2] = heading[2];
	
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