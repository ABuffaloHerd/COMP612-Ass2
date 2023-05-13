#include "Helicopter.h"

extern const float FRAME_TIME_SEC;

#define SPINRATE 1000.0f
#define TEACUP_DIST 4.0f
#define COPTER_SCALE 2.0


void render_helicopter(GameObject* this)
{
	static float proprot = 0.0f; // propeller rotation

	glColor4d(0.8, 0.8, 0.8, 1.0);

	glPushMatrix(); // push the body

	// Body
	glTranslatef(this->pos[0], this->pos[1], this->pos[2]);

	glRotatef(this->rot[0], 1, 0, 0);
	glRotatef(this->rot[1], 0, 1, 0);
	glRotatef(this->rot[2], 0, 0, 1);

	glutSolidTeapot(COPTER_SCALE);

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

	glPopMatrix(); // pop the body

	proprot += SPINRATE * FRAME_TIME_SEC; // update rotor angle
}

void update_helicopter(GameObject* this)
{
	this->rot[1] = modf(this->rot[1], 360);
}