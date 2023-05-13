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
	//printf("test");
}

void test_render(int mode)
{
	glPushMatrix();

	glColor3f(0.5f, 0.5f, 0.5f);
	
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3d(10.0, 0.0, -10.0);
	glVertex3d(-10.0, 0.0, -10.0);
	glVertex3d(-10.0, 0.0, 10.0);
	glVertex3d(10.0, 0.0, 10.0);
	glEnd();

	glPopMatrix();
}

void drawOrigin(void)
{
	glBegin(GL_LINES);
	//draw red x axes line from -2.0 to 2.0
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3d(-0.0, 0.0, 0.0);
	glVertex3d(2.0, 0.0, 0.0);

	//draw blue y axes line from -2.0 to 2.0
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3d(0.0, 2.0, 0.0);
	glVertex3d(0.0, -0.0, 0.0);

	//draw green z axes line from -2.0 to 2.0
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3d(0.0, 0.0, 2.0);
	glVertex3d(0.0, 0.0, -0.0);

	glEnd();
}

void render_grid(void)
{
	int gridSize = 10000;
	int cellSize = 10;
	int halfGridSize = gridSize / 2;

	glColor3f(0.7f, 0.7f, 0.7f); // Set grid color

	glBegin(GL_LINES);
	for (int i = -halfGridSize; i <= halfGridSize; i += cellSize)
	{
		// Horizontal lines
		glVertex3f(-halfGridSize, 0, i);
		glVertex3f(halfGridSize, 0, i);

		// Vertical lines
		glVertex3f(i, 0, -halfGridSize);
		glVertex3f(i, 0, halfGridSize);
	}
	glEnd();
}