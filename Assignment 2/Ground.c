#include <freeglut.h>
#include "Ground.h"
#include "Misc.h"
#include <stdio.h>
#include "Texture.h"

const int size = 100;
const int quadSize = 10;
extern int renderFillEnabled;

void render_ground(void)
{
	printf("renderground has been called\n");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureRegistry[TEXTURE_TROLL]);
	//glBindTexture(GL_TEXTURE_2D, 0); 

	glBegin(GL_QUADS);
	int x = 1;
	int z = 1;

		glNormal3i(0, 1, 0);
		glTexCoord2i(TOPRIGHT);
		glVertex3i(5, 0, 5);

		glNormal3i(0, 1, 0);
		glTexCoord2i(TOPLEFT);
		glVertex3i(-5, 0, 5);

		glNormal3i(0, 1, 0);
		glTexCoord2i(BOTTOMLEFT);
		glVertex3i(-5, 0, -5);

		glNormal3i(0, 1, 0);
		glTexCoord2i(BOTTOMRIGHT);
		glVertex3i(5, 0, -5);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void test_render(int mode)
{
	glPushMatrix();

	setMaterialColor(0.5f, 0.5f, 0.5f);
	
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
	setMaterialColor(1.0f, 0.0f, 0.0f);
	glVertex3d(-0.0, 0.0, 0.0);
	glVertex3d(2.0, 0.0, 0.0);

	//draw blue y axes line from -2.0 to 2.0
	setMaterialColor(0.0f, 0.0f, 1.0f);
	glVertex3d(0.0, 2.0, 0.0);
	glVertex3d(0.0, -0.0, 0.0);

	//draw green z axes line from -2.0 to 2.0
	setMaterialColor(0.0f, 1.0f, 0.0f);
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

	setMaterialColor(0.0f, 0.0f, 0.0f); // Set grid color

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