/*
* Test project for 3d assignment later.
*/

#include <freeglut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include "Object.h"

void drawOrigin(void);

// Target frame rate (number of Frames Per Second).
#define TARGET_FPS 120				

// Ideal time each frame should be displayed for (in milliseconds).
const unsigned int FRAME_TIME = 1000 / TARGET_FPS;

// Frame time in seconds
const float FRAME_TIME_SEC = (1000 / TARGET_FPS) / 1000.0f;

// total running time
unsigned int frameStartTime = 0;

Model planets[5];

void init(void)
{
	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set background color to be black
	glClearColor(0, 0, 0, 1.0);

	// NOTE: Don't need to set up projection here anymore
	//       since the reshape callback function will be called when
	//		 the window is first created

	//need some lighting or our cup will look flat!
	// Configure global ambient lighting.
	// Simple lighting setup
	GLfloat globalAmbient[] = { 0.8f, 0.8f, 0.8f, 1 };
	GLfloat diffuseLight[] = { 1, 1, 1, 1 };
	GLfloat specularLight[] = { 1, 1, 1, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Make GL normalize the normal vectors we supply.
	glEnable(GL_NORMALIZE);

	// Enable use of simple GL colours as materials.
	glEnable(GL_COLOR_MATERIAL);

	// planets
	planets[0].pos[0] = 0;
	planets[0].pos[1] = 0;
	planets[0].pos[2] = 0;

	planets[0].rot[0] = 0;
	planets[0].rot[1] = 0;
	planets[0].rot[2] = 0;
}

void reshape(int w, int h)
{
	// update the new width
	int windowWidth = w;
	// update the new height
	int windowHeight = h;

	// update the viewport to still be all of the window
	glViewport(0, 0, windowWidth, windowHeight);

	// change into projection mode so that we can change the camera properties
	glMatrixMode(GL_PROJECTION);

	// load the identity matrix into the projection matrix
	glLoadIdentity();

	// gluPerspective(fovy, aspect, near, far)
	gluPerspective(45, (float)windowWidth / (float)windowHeight, 1, 20);

	// change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);
}

void think(void)
{

}

void display(void)
{
	// clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix into the model view matrix
	glLoadIdentity();

	gluLookAt(10, 10, 10,
		0, 0, 0,
		0, 1, 0);
	
	// center planet
	glColor3f(0.5f, 0.0f, 0.5f);
	glutSolidSphere(2, 20, 20);

	glColor3f(0.1f, 0.2, 0.6f);
	glPushMatrix();
	glTranslatef(4.5f, 0, 0);
	glutSolidTeapot(1);
	//glPopMatrix();

	glColor3f(1.0f, 0.0f, 0.1f);
	//glPushMatrix();
	glTranslatef(0, 0, 1.5f);
	glutSolidTeaspoon(1);
	//glPopMatrix();
	glPopMatrix();

	drawOrigin();

	// swap the drawing buffers
	glutSwapBuffers();
}

void idle(void)
{
	// Wait until it's time to render the next frame.
	unsigned int frameTimeElapsed = (unsigned int)glutGet(GLUT_ELAPSED_TIME) - frameStartTime;
	if (frameTimeElapsed < FRAME_TIME)
	{
		// This frame took less time to render than the ideal FRAME_TIME: we'll suspend this thread for the remaining time,
		unsigned int timeLeft = FRAME_TIME - frameTimeElapsed;
		Sleep(timeLeft);
	}

	// Begin processing the next frame.

	frameStartTime = glutGet(GLUT_ELAPSED_TIME); // Record when we started work on the new frame.

	think(); // Update our simulated world before the next call to display().

	glutPostRedisplay(); // Tell OpenGL there's a new frame ready to be drawn.
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Planets");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
}

void drawOrigin(void)
{
	glBegin(GL_LINES);
	//draw red x axes line from -2.0 to 2.0
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3d(-2.0, 0.0, 0.0);
	glVertex3d(2.0, 0.0, 0.0);

	//draw blue y axes line from -2.0 to 2.0
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3d(0.0, 2.0, 0.0);
	glVertex3d(0.0, -2.0, 0.0);

	//draw green z axes line from -2.0 to 2.0
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3d(0.0, 0.0, 2.0);
	glVertex3d(0.0, 0.0, -2.0);

	glEnd();
}
