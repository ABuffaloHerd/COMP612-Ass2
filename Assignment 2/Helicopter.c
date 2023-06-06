#include "Helicopter.h"

extern const float FRAME_TIME_SEC;
extern RenderList* renderList;

#define SPINRATE 1000.0f
#define TEACUP_DIST 4.0f
#define COPTER_SCALE 2.0

void render_helicopter(GameObject* this)
{
	static float proprot = 0.0f; // propeller rotation

	reset_material_properties();

	setMaterialColor(1.0f, 1.0f, 1.0f); // set material color

	glPushMatrix(); // push the body

		// Body
		glTranslatef(this->pos[0], this->pos[1], this->pos[2]);

		glRotatef(this->rot[0], 1, 0, 0);
		glRotatef(this->rot[1], 0, 1, 0);
		glRotatef(this->rot[2], 0, 0, 1);

		// shiny ass teapot
		GLfloat teapotcolour[] = { 0.0f, 0.8f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, teapotcolour);
		glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);

		glutSolidTeapot(COPTER_SCALE);

		// tail
		glPushMatrix();

			GLfloat pink[] = { 0.990, 0.505, 0.537, 1.0f };
			GLfloat pink2[] = { 0.990, 0.713, 0.713, 1.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pink);
			glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);

			glRotated(-90, 0.0, 1.0, 0.0);
			glutSolidCylinder(0.5, 4 * COPTER_SCALE, 20, 20);

			glTranslated(0.0, 0.0, 4 * COPTER_SCALE);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pink2);
			glutSolidCone(0.5, 1.0, 10, 10);

			// tail propeller, bound to the tail position

			glPushMatrix();
				// move to the side 
				glTranslated(-0.5, 0.0, 0.0);
				glRotated(90, 0.0, 0.0, 1.0); // rotate to the side
				glRotated(proprot, 0.0, 1.0, 0.0); // turn the rotors

				glScaled(2.0, 0.1, 0.1);

				GLfloat pissyellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
				GLfloat orang[] = { 0.990, 0.293, 0.119 , 1.0f };
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orang);
				glMaterialfv(GL_FRONT, GL_EMISSION, pissyellow);
				glutSolidCube(1);

			glPopMatrix();  // pop the tail propeller
	
		glPopMatrix(); // pop the tail

		// Propeller

		reset_material_properties();
		// boring steel grey
		GLfloat boring[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, boring);
		glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);

		glPushMatrix();
			glTranslated(0.0, 1.5, 0.0);
			glRotatef(proprot, 0.0f, 1.0f, 0.0f);
			glScaled(15.0, 0.1, 1.0);

			glutSolidCube(1);
		glPopMatrix();
	
		glPushMatrix(); // second blade

			glTranslated(0.0, 1.5, 0.0);
			glRotatef(proprot + 90.0f, 0.0f, 1.0f, 0.0f);
			glScaled(15.0, 0.1, 1.0);
			glutSolidCube(1);

		glPopMatrix(); // pop the rotors

		// Teacup weaponry
		glPushMatrix();
			glTranslated(0.0, 0.0, TEACUP_DIST);
			glutSolidTeacup(1);
		glPopMatrix();

		// teacup 2
		glPushMatrix();
			glTranslated(0.0, 0.0, -TEACUP_DIST);
			glutSolidTeacup(1);
		glPopMatrix(); // pop the weapons

		// things that hold the teacups in place
		glPushMatrix();
			glTranslated(0.0, -0.3, 0.0);
			glScaled(0.1, 0.01, TEACUP_DIST / 2);
			glutSolidCube(TEACUP_DIST);
		glPopMatrix();

	// lights
		glPushMatrix();
			//glLoadIdentity(); // hard reset the transformation matrix to make sure the light is in the right fucking position

			// set position of this light
			GLfloat pos[] = { 0, -0.5f, 0, 1.0f};
			glLightfv(GL_LIGHT1, GL_POSITION, pos);

			// set the colours
			GLfloat colour[] = { 1.0, 1.0, 1.0, 1.0 };
			glLightfv(GL_LIGHT1, GL_DIFFUSE, colour);
			glLightfv(GL_LIGHT1, GL_SPECULAR, colour);

			// set some properties
			GLfloat down[] = { 0.0f, -1.0f, 0.0f };
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, down);
			glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f);

		glPopMatrix();

	glPopMatrix(); // pop the body

	proprot += SPINRATE * FRAME_TIME_SEC; // update rotor angle
}

void render_enemy_helicopter(GameObject* this)
{
	static float proprot = 0.0f; // propeller rotation

	reset_material_properties();

	setMaterialColor(1.0f, 0.0f, 0.0f); // set material color
	// glow purpleish
	GLfloat purpur[] = { 1.0f, 0.0f, 0.1f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, purpur);

	glPushMatrix(); // push the body

	// Body
	glTranslatef(this->pos[0], this->pos[1], this->pos[2]);

	glRotatef(this->rot[0], 1, 0, 0);
	glRotatef(this->rot[1], 0, 1, 0);
	glRotatef(this->rot[2], 0, 0, 1);

	glutSolidTeapot(COPTER_SCALE);

	// reset colours
	reset_material_properties();
	setMaterialColor(1.0f, 0.0f, 0.0f); 

	// tail
	glPushMatrix();

	glRotated(-90, 0.0, 1.0, 0.0);
	glutSolidCylinder(0.5, 4 * COPTER_SCALE, 20, 20);

	glTranslated(0.0, 0.0, 4 * COPTER_SCALE);

	glutSolidCone(0.5, 1.0, 10, 10);

	// tail propeller, bound to the tail position

	glPushMatrix();
	// move to the side 
	glTranslated(-0.5, 0.0, 0.0);
	glRotated(90, 0.0, 0.0, 1.0); // rotate to the side
	glRotated(proprot, 0.0, 1.0, 0.0); // turn the rotors

	glScaled(2.0, 0.1, 0.1);

	glutSolidCube(1);

	glPopMatrix();  // pop the tail propeller

	glPopMatrix(); // pop the tail

	// Propeller

	glPushMatrix();
	glTranslated(0.0, 1.5, 0.0);
	glRotatef(proprot, 0.0f, 1.0f, 0.0f);
	glScaled(15.0, 0.1, 1.0);

	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); // second blade

	glTranslated(0.0, 1.5, 0.0);
	glRotatef(proprot + 90.0f, 0.0f, 1.0f, 0.0f);
	glScaled(15.0, 0.1, 1.0);
	glutSolidCube(1);

	glPopMatrix(); // pop the rotors

	// Teacup weaponry
	glPushMatrix();
	glTranslated(0.0, 0.0, TEACUP_DIST);
	glutSolidTeacup(1);
	glPopMatrix();

	// teacup 2
	glPushMatrix();
	glTranslated(0.0, 0.0, -TEACUP_DIST);
	glutSolidTeacup(1);
	glPopMatrix(); // pop the weapons

	// things that hold the teacups in place
	glPushMatrix();
	glTranslated(0.0, -0.3, 0.0);
	glScaled(0.1, 0.01, TEACUP_DIST / 2);
	glutSolidCube(TEACUP_DIST);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix(); // pop the body

	reset_material_properties();

	proprot += SPINRATE * FRAME_TIME_SEC; // update rotor angle
}

void update_helicopter(GameObject* this)
{
	this->rot[1] = modf(this->rot[1], 360);
}

#define THRESHOLD 0.09f // distance tolerance
int checkpos(GLfloat here[3], GLfloat there[3])
{
	GLfloat dx = here[0] - there[0];
	GLfloat dy = here[1] - there[1];
	GLfloat dz = here[2] - there[2];

	GLfloat distance = sqrt(dx * dx + dy * dy + dz * dz);

	return distance < THRESHOLD; // i don't actually know what it returns, just that if it fails it's 0
}

void toggle_enemy(GameObject* enemy)
{
	if (enemy->update)
	{
		enemy->update = 0;
	}
	else enemy->update = update_enemy_helicopter;
}

void update_enemy_helicopter(GameObject* enemy)
{
	static unsigned int framecount = 0; // used to time state changes
	static GLfloat positions[10][3] = 
	{
		{400.0f, 50.0f, 25.0f},  // Top middle
		{425.0f, 50.0f, 0.0f},   // Top right
		{400.0f, 50.0f, -25.0f}, // Bottom right
		{375.0f, 50.0f, 0.0f},   // Bottom middle
		{400.0f, 70.0f, 0.0f},   // Above center
		{400.0f, 30.0f, 0.0f},   // Below center
		{412.5f, 70.0f, 12.5f},  // Above top right
		{387.5f, 70.0f, -12.5f}, // Above top left
		{412.5f, 30.0f, -12.5f}, // Below bottom right
		{387.5f, 30.0f, 12.5f}   // Below bottom left
	};
	static unsigned int pos_index = 0; // index of the current target position

	static AIState state = IDLE; // start idle

	// update the frame count
	framecount++;

	// check state and decide what to do
	switch (state)
	{
	case IDLE:
		printf("Enemy AI: IDLE\n");
		break;
	case MOVE:
		// move towards the next position
		// i have accidentally implemented easing. i'm not even mad
		enemy->pos[0] += (positions[pos_index][0] - enemy->pos[0]) * FRAME_TIME_SEC * 5;
		enemy->pos[1] += (positions[pos_index][1] - enemy->pos[1]) * FRAME_TIME_SEC * 5;
		enemy->pos[2] += (positions[pos_index][2] - enemy->pos[2]) * FRAME_TIME_SEC * 5;
		printf("Enemy AI: MOVE\n");
		break;
	case SHOOT: // one bullet per frame.
		printf("Enemy AI: SHOOT\n");
		renderlist_push(renderList, instantiate_bullet(enemy->pos));
		break;
	}

	// check if we should change state
	if (framecount % 480 == 0 && state != MOVE)
	{
		printf("Enemy AI: CHANGING STATE TO MOVE\n");
		state = MOVE;
	}
	else if (state == MOVE && checkpos(enemy->pos, positions[pos_index]))
	{
		printf("Enemy AI: CHANGING STATE TO IDLE\n");
		state = IDLE;
		pos_index >= 10 ? pos_index = 0 : pos_index++;
	}
	else if (framecount % 120 == 0 && state == IDLE)
	{
		printf("Enemy AI: CHANGING STATE TO SHOOT\n");
		printf("Jedi! Blast em'!\n");
		state = SHOOT;
	}
}