#include <freeglut.h>
#include "Ground.h"
#include <stdio.h>

const int size = 1000;
extern int renderFillEnabled;

void render_ground(float quadSize)
{
	// Save current state
	glPushMatrix();

	// Set the color for the ground plane
	glColor3f(0.2f, 0.2f, 0.2f);

	// Draw the ground plane as a grid of quads
	for (int x = -size; x < size; x++) 
	{
		for (int z = -size; z < size; z++) 
		{
			glBegin(GL_QUADS);
			glNormal3i(0, 1, 0);
			glVertex3f(x * quadSize, 0, z * quadSize);
			glNormal3i(0, 1, 0);
			glVertex3f(x * quadSize, 0, (z + 1) * quadSize);
			glNormal3i(0, 1, 0);
			glVertex3f((x + 1) * quadSize, 0, (z + 1) * quadSize);
			glNormal3i(0, 1, 0);
			glVertex3f((x + 1) * quadSize, 0, z * quadSize);
			glEnd();
		}
	}

	// Restore previous state
	glPopMatrix();
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
	if (renderFillEnabled) return;
	int gridSize = 10000;
	int cellSize = 10;
	int halfGridSize = gridSize / 2;

	glColor3f(0.0f, 0.0f, 0.0f); // Set grid color

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