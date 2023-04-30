#include <freeglut.h>
#include "Ground.h"
#include <stdio.h>

const int size = 10;

void render_ground(int mode)
{
	// set colour to a tasteless gray for now
	glColor3f(0.5f, 0.5f, 0.5f);


	if (mode) // solid
	{
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f); // face up
		glVertex3f(-size, 0.0f, -size);
		glVertex3f(-size, 0.0f, size);
		glVertex3f(size, 0.0f, size);
		glVertex3f(size, 0.0f, -size);
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
		glEnd();
	}
	printf("test");
}

void test_render(int mode)
{
	glPushMatrix();

	GLUquadricObj* obj = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, 2.0f);

	glutSolidTorus(0.5, 1.5, 20, 10);
	glPopMatrix();
}