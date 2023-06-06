#include <freeglut.h>
#include "Ground.h"
#include "Misc.h"
#include <stdio.h>
#include "Texture.h"

extern int renderFillEnabled;

void render_ground(void)
{
	glEnable(GL_TEXTURE_2D);
	bind_texture(TEXTURE_GROUND);

	glBegin(GL_QUADS);
	for (int x = -GROUNDSIZE; x < GROUNDSIZE; x++) 
	{
		for (int z = -GROUNDSIZE; z < GROUNDSIZE; z++) 
		{
			// Bottom Right vertex
			glTexCoord2i(1, 0);
			glNormal3i(0, 1, 0);
			glVertex3f((x + 1) * GROUND_QUADSIZE, 0, z * GROUND_QUADSIZE);

			// Top Right vertex
			glTexCoord2i(1, 1);
			glNormal3i(0, 1, 0);
			glVertex3f((x + 1) * GROUND_QUADSIZE, 0, (z + 1) * GROUND_QUADSIZE);

			// Top Left vertex
			glTexCoord2i(0, 1);
			glNormal3i(0, 1, 0);
			glVertex3f(x * GROUND_QUADSIZE, 0, (z + 1) * GROUND_QUADSIZE);

			// Bottom Left vertex
			glTexCoord2i(0, 0);
			glNormal3i(0, 1, 0);
			glVertex3f(x * GROUND_QUADSIZE, 0, z * GROUND_QUADSIZE);

		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void render_road(void)
{
	reset_material_properties();
	glEnable(GL_TEXTURE_2D);
	bind_texture(TEXTURE_ROAD);

	glPushMatrix();
	glTranslatef(0, 0, -45); // shove the road further away into the z axis

	glBegin(GL_QUAD_STRIP);

	// The magic number 5 strikes again. Or maybe it's GROUNDSIZE. It is isn't it.
	// The road is 2 * GROUNDSIZE units wide.
	for (int i = -GROUNDSIZE * 5; i < GROUNDSIZE * 5; i += GROUND_QUADSIZE) 
	{
		// Top vertex
		glNormal3f(0, 1, 0); // Normal pointing up along the Y axis
		glTexCoord2i(1, i % 2); // who knew a gin and tonic was all it took to type % 2
		glVertex3f(i, 0.01f, GROUND_QUADSIZE * 2);

		// Bottom vertex
		glNormal3f(0, 1, 0); // Normal pointing up along the Y axis
		glTexCoord2i(0, i % 2);
		glVertex3f(i, 0.01f, 0);
	}

	glEnd();

	glPopMatrix();
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