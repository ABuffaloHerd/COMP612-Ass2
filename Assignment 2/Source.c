/******************************************************************************
 *
 * Computer Graphics Programming 2020 Project Template v1.0 (11/04/2021)
 *
 * Based on: Animation Controller v1.0 (11/04/2021)
 *
 * This template provides a basic FPS-limited render loop for an animated scene,
 * plus keyboard handling for smooth game-like control of an object such as a
 * character or vehicle.
 *
 * A simple static lighting setup is provided via initLights(), which is not
 * included in the animationalcontrol.c template. There are no other changes.
 *
 ******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS // i am on my knees begging for a buffer overflow
#pragma warning(disable:4996) // FUCKING LET ME COMPILE YOU PIECE OF SHITA

#include <Windows.h>
#include <freeglut.h>
#include <math.h>
#include <time.h>

#include "Ground.h"
#include "Camera.h"
#include "GameObject.h"
#include "Helicopter.h"
#include "SoundSystem.h"
#include "Texture.h"
#include "DisplayList.h"
#include "RenderList.h"
#include "StaticObjects.h"
 /******************************************************************************
  * Animation & Timing Setup
  ******************************************************************************/

  // Target frame rate (number of Frames Per Second).
#define TARGET_FPS 120				

// Ideal time each frame should be displayed for (in milliseconds).
const unsigned int FRAME_TIME = 1000 / TARGET_FPS;

// Frame time in fractional seconds.
// Note: This is calculated to accurately reflect the truncated integer value of
// FRAME_TIME, which is used for timing, rather than the more accurate fractional
// value we'd get if we simply calculated "FRAME_TIME_SEC = 1.0f / TARGET_FPS".
const float FRAME_TIME_SEC = (1000 / TARGET_FPS) / 1000.0f;


// Time we started preparing the current frame (in milliseconds since GLUT was initialized).
unsigned int frameStartTime = 0;


// Total frames since program started.
// it's okay to leave this adding because 1) it overflows 2) 18,446,744,073,709,551,615 is the limit
long long unsigned int frameCount = 0;


/******************************************************************************
 * Some Simple Definitions of Motion
 ******************************************************************************/

#define MOTION_NONE 0				// No motion.
#define MOTION_CLOCKWISE -1			// Clockwise rotation.
#define MOTION_ANTICLOCKWISE 1		// Anticlockwise rotation.
#define MOTION_BACKWARD -1			// Backward motion.
#define MOTION_FORWARD 1			// Forward motion.
#define MOTION_LEFT -1				// Leftward motion.
#define MOTION_RIGHT 1				// Rightward motion.
#define MOTION_DOWN -1				// Downward motion.
#define MOTION_UP 1					// Upward motion.

#define MOTION_LOOK_UP 1
#define MOTION_LOOK_DOWN -1
#define MOTION_ZOOM_IN 1
#define MOTION_ZOOM_OUT -1

 // Represents the motion of an object on four axes (Yaw, Surge, Sway, and Heave).
 // 
 // You can use any numeric values, as specified in the comments for each axis. However,
 // the MOTION_ definitions offer an easy way to define a "unit" movement without using
 // magic numbers (e.g. instead of setting Surge = 1, you can set Surge = MOTION_FORWARD).
 //
typedef struct {
	int Yaw;		// Turn about the Z axis	[<0 = Clockwise, 0 = Stop, >0 = Anticlockwise]
	int Surge;		// Move forward or back		[<0 = Backward,	0 = Stop, >0 = Forward]
	int Sway;		// Move sideways (strafe)	[<0 = Left, 0 = Stop, >0 = Right]
	int Heave;		// Move vertically			[<0 = Down, 0 = Stop, >0 = Up]
} motionstate4_t;

// represents camera motion
typedef struct _cammotion
{
	int Zoom;
	int Tilt;
} cameramotion_t;

/******************************************************************************
 * Keyboard Input Handling Setup
 ******************************************************************************/

 // Represents the state of a single keyboard key.Represents the state of a single keyboard key.
typedef enum {
	KEYSTATE_UP = 0,	// Key is not pressed.
	KEYSTATE_DOWN		// Key is pressed down.
} keystate_t;

// Represents the states of a set of keys used to control an object's motion.
typedef struct {
	keystate_t MoveForward;
	keystate_t MoveBackward;
	keystate_t MoveLeft;
	keystate_t MoveRight;
	keystate_t MoveUp;
	keystate_t MoveDown;
	keystate_t TurnLeft;
	keystate_t TurnRight;
} motionkeys_t;

typedef struct _camkeys
{
	keystate_t ZoomIn;
	keystate_t ZoomOut;
	keystate_t TiltUp;
	keystate_t TiltDown;
} camkeys_t;

// Current state of all keys used to control our "player-controlled" object's motion.
motionkeys_t motionKeyStates = {
	KEYSTATE_UP, KEYSTATE_UP, KEYSTATE_UP, KEYSTATE_UP,
	KEYSTATE_UP, KEYSTATE_UP, KEYSTATE_UP, KEYSTATE_UP };

// state of keys used to control camera
camkeys_t camKeyStates = 
{
	KEYSTATE_UP, KEYSTATE_UP, KEYSTATE_UP, KEYSTATE_UP 
};

// How our "player-controlled" object should currently be moving, solely based on keyboard input.
//
// Note: this may not represent the actual motion of our object, which could be subject to
// other controls (e.g. mouse input) or other simulated forces (e.g. gravity).
motionstate4_t keyboardMotion = { MOTION_NONE, MOTION_NONE, MOTION_NONE, MOTION_NONE };

// how the camera should currently be moving, solely based on keyboard input
cameramotion_t keyboardCameraMotion = { MOTION_NONE, MOTION_NONE };

// Define all character keys used for input (add any new key definitions here).
// Note: USE ONLY LOWERCASE CHARACTERS HERE. The keyboard handler provided converts all
// characters typed by the user to lowercase, so the SHIFT key is ignored.

#define KEY_MOVE_FORWARD	'w'
#define KEY_MOVE_BACKWARD	's'
#define KEY_MOVE_LEFT		'a'
#define KEY_MOVE_RIGHT		'd'
#define KEY_RENDER_FILL		'l'
#define KEY_EXIT			27 // Escape key.

#define KEY_TOGGLE_TARGET	't'
#define KEY_CAMERA_LOCK		'c'

#define KEY_TILT_UP			'f'
#define KEY_TILT_DOWN		'v'

#define KEY_ZOOM_IN			'='
#define KEY_ZOOM_OUT		'-'

#define KEY_DEBUG_SOUND		'0'
#define KEY_TOGGLE_LIGHTING	'1'

#define KEY_FIRE_MISSILE	32 // space

#define KEY_TOGGLE_BOSS		'b'
#define KEY_TELEPORT		'p'


// Define all GLUT special keys used for input (add any new key definitions here).

#define SP_KEY_MOVE_UP		GLUT_KEY_UP
#define SP_KEY_MOVE_DOWN	GLUT_KEY_DOWN
#define SP_KEY_TURN_LEFT	GLUT_KEY_LEFT
#define SP_KEY_TURN_RIGHT	GLUT_KEY_RIGHT

/******************************************************************************
 * GLUT Callback Prototypes
 ******************************************************************************/

void display(void);
void reshape(int width, int h);
void keyPressed(unsigned char key, int x, int y);
void specialKeyPressed(int key, int x, int y);
void keyReleased(unsigned char key, int x, int y);
void specialKeyReleased(int key, int x, int y);
void idle(void);

/******************************************************************************
 * Animation-Specific Function Prototypes (add your own here)
 ******************************************************************************/

void main(int argc, char** argv);
void init(void);
void think(void);
void initLights(void);

void init_gameobjects(void);
void fogger(void);
void init_cylinders(void);

// DEFINITIONS OF DISTANCE
#define METER 1.0 // 1m = 1.0 glunits

/******************************************************************************
 * Animation-Specific Setup (Add your own definitions, constants, and globals here)
 ******************************************************************************/

 // Render objects as filled polygons (1) or wireframes (0). Default filled.
int renderFillEnabled = 1;

// push missile 
unsigned int pushMissile = 0;

// Camera position and orientation. Also a global variable ho ho ho!
Camera* c;

// copters
GameObject* copter;
GameObject* enemyCopter;

// DIsplay list inator
DisplayList* displayList;

// Render list inator
RenderList* renderList;

inline float randf() 
{
	return (float)rand() / (float)RAND_MAX;
}

void randomPointOnSphere(float r, float* x, float* y, float* z) 
{
	// Generate random azimuthal angle (theta) and polar angle (phi)
	float theta = 2.0f * 3.14159 * randf();
	float phi = acos(2.0f * randf() - 1.0f);

	// Convert from spherical to Cartesian coordinates
	*x = r * sin(phi) * cos(theta);
	*y = r * sin(phi) * sin(theta);
	*z = r * cos(phi);
}

/******************************************************************************
 * Entry Point (don't put anything except the main function here)
 ******************************************************************************/

void main(int argc, char** argv)
{
	// Initialize the OpenGL window.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("The Battle of Britain II");

	// Set up the scene.
	init();

	// Disable key repeat (keyPressed or specialKeyPressed will only be called once when a key is first pressed).
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	// Register GLUT callbacks.
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutSpecialUpFunc(specialKeyReleased);
	glutIdleFunc(idle);

	// Record when we started rendering the very first frame (which should happen after we call glutMainLoop).
	frameStartTime = (unsigned int)glutGet(GLUT_ELAPSED_TIME);

	// Enter the main drawing loop (this will never return).
	glutMainLoop();
}

/******************************************************************************
 * GLUT Callbacks (don't add any other functions here)
 ******************************************************************************/

 /*
	 Called when GLUT wants us to (re)draw the current animation frame.

	 Note: This function must not do anything to update the state of our simulated
	 world. Animation (moving or rotating things, responding to keyboard input,
	 etc.) should only be performed within the think() function provided below.
 */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Camera looks at whatever the controlled object is
	// camera update handles the positioning
	gluLookAt(c->pos[0], c->pos[1], c->pos[2],
		copter->pos[0], copter->pos[1], copter->pos[2],
		0, 1, 0);


	// render objects
	copter->render(copter);

	// Render static objects
	render_displaylist(displayList);
	renderlist_render(renderList);

	drawOrigin();

	glutSwapBuffers();
}

/*
	Called when the OpenGL window has been resized.
*/
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
	gluPerspective(60, (float)windowWidth / (float)windowHeight, 1, 2000);

	// change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);
}

/*
	Called each time a character key (e.g. a letter, number, or symbol) is pressed.
*/
void keyPressed(unsigned char key, int x, int y)
{
	switch (tolower(key)) {

		/*
			Keyboard-Controlled Motion Handler - DON'T CHANGE THIS SECTION

			Whenever one of our movement keys is pressed, we do two things:
			(1) Update motionKeyStates to record that the key is held down. We use
				this later in the keyReleased callback.
			(2) Update the relevant axis in keyboardMotion to set the new direction
				we should be moving in. The most recent key always "wins" (e.g. if
				you're holding down KEY_MOVE_LEFT then also pressed KEY_MOVE_RIGHT,
				our object will immediately start moving right).
		*/
	case KEY_MOVE_FORWARD:
		motionKeyStates.MoveForward = KEYSTATE_DOWN;
		keyboardMotion.Surge = MOTION_FORWARD;
		break;
	case KEY_MOVE_BACKWARD:
		motionKeyStates.MoveBackward = KEYSTATE_DOWN;
		keyboardMotion.Surge = MOTION_BACKWARD;
		break;
	case KEY_MOVE_LEFT:
		motionKeyStates.MoveLeft = KEYSTATE_DOWN;
		keyboardMotion.Sway = MOTION_LEFT;
		break;
	case KEY_MOVE_RIGHT:
		motionKeyStates.MoveRight = KEYSTATE_DOWN;
		keyboardMotion.Sway = MOTION_RIGHT;
		break;

		/*
			I AM IGNORING THE COMMENT AND MODIFYING THIS SECTION HAHAHAHAHA
		*/
	case KEY_TILT_UP:
		camKeyStates.TiltUp = KEYSTATE_DOWN;
		keyboardCameraMotion.Tilt = MOTION_LOOK_UP;
		break;
	case KEY_TILT_DOWN:
		camKeyStates.TiltDown = KEYSTATE_DOWN;
		keyboardCameraMotion.Tilt = MOTION_LOOK_DOWN;
		break;
	case KEY_ZOOM_IN:
		camKeyStates.ZoomIn = KEYSTATE_DOWN;
		keyboardCameraMotion.Zoom = MOTION_ZOOM_IN;
		break;
	case KEY_ZOOM_OUT:
		camKeyStates.ZoomOut = KEYSTATE_DOWN;
		keyboardCameraMotion.Zoom = MOTION_ZOOM_OUT;
		break;

		/*
			Other Keyboard Functions (add any new character key controls here)

			Rather than using literals (e.g. "t" for spotlight), create a new KEY_
			definition in the "Keyboard Input Handling Setup" section of this file.
			For example, refer to the existing keys used here (KEY_MOVE_FORWARD,
			KEY_MOVE_LEFT, KEY_EXIT, etc).
		*/
	case KEY_CAMERA_LOCK:
		c->locked = !c->locked;
		//printf("camera lock toggled\n");
		break;

	//case KEY_TILT_UP:
	//	c->rot[0] += 500 * FRAME_TIME_SEC;
	//	break;
	//case KEY_TILT_DOWN:
	//	c->rot[0] -= 500 * FRAME_TIME_SEC;
	//	break;

	//case KEY_ZOOM_IN:
	//	c->dist -= 5;
	//	break;
	//case KEY_ZOOM_OUT:
	//	c->dist += 5;
	//	break;

	case KEY_DEBUG_SOUND:
		play_sound(SOUND_EXPLODE);
		break;
	case KEY_TOGGLE_LIGHTING:
		if(glIsEnabled(GL_LIGHT1))
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);
		break;

	case KEY_TOGGLE_BOSS:
		toggle_enemy(enemyCopter);
		break;
	case KEY_TELEPORT:
		copter->pos[0] = 300;
		copter->pos[1] = 50;
		copter->pos[2] = 0;
		break;

	case KEY_FIRE_MISSILE: // no functions here
		pushMissile = 1;
		break;

	case KEY_RENDER_FILL:
		renderFillEnabled = !renderFillEnabled;
		if (renderFillEnabled)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case KEY_EXIT:
		exit(0);
		break;
	}
}

/*
	Called each time a "special" key (e.g. an arrow key) is pressed.
*/
void specialKeyPressed(int key, int x, int y)
{
	switch (key) {

		/*
			Keyboard-Controlled Motion Handler - DON'T CHANGE THIS SECTION

			This works as per the motion keys in keyPressed.
		*/
	case SP_KEY_MOVE_UP:
		motionKeyStates.MoveUp = KEYSTATE_DOWN;
		keyboardMotion.Heave = MOTION_UP;
		break;
	case SP_KEY_MOVE_DOWN:
		motionKeyStates.MoveDown = KEYSTATE_DOWN;
		keyboardMotion.Heave = MOTION_DOWN;
		break;
	case SP_KEY_TURN_LEFT:
		motionKeyStates.TurnLeft = KEYSTATE_DOWN;
		keyboardMotion.Yaw = MOTION_ANTICLOCKWISE;
		break;
	case SP_KEY_TURN_RIGHT:
		motionKeyStates.TurnRight = KEYSTATE_DOWN;
		keyboardMotion.Yaw = MOTION_CLOCKWISE;
		break;

		/*
			Other Keyboard Functions (add any new special key controls here)

			Rather than directly using the GLUT constants (e.g. GLUT_KEY_F1), create
			a new SP_KEY_ definition in the "Keyboard Input Handling Setup" section of
			this file. For example, refer to the existing keys used here (SP_KEY_MOVE_UP,
			SP_KEY_TURN_LEFT, etc).
		*/
	}
}

/*
	Called each time a character key (e.g. a letter, number, or symbol) is released.
*/
void keyReleased(unsigned char key, int x, int y)
{
	switch (tolower(key)) {

		/*
			Keyboard-Controlled Motion Handler - DON'T CHANGE THIS SECTION

			Whenever one of our movement keys is released, we do two things:
			(1) Update motionKeyStates to record that the key is no longer held down;
				we need to know when we get to step (2) below.
			(2) Update the relevant axis in keyboardMotion to set the new direction
				we should be moving in. This gets a little complicated to ensure
				the controls work smoothly. When the user releases a key that moves
				in one direction (e.g. KEY_MOVE_RIGHT), we check if its "opposite"
				key (e.g. KEY_MOVE_LEFT) is pressed down. If it is, we begin moving
				in that direction instead. Otherwise, we just stop moving.
		*/
	case KEY_MOVE_FORWARD:
		motionKeyStates.MoveForward = KEYSTATE_UP;
		keyboardMotion.Surge = (motionKeyStates.MoveBackward == KEYSTATE_DOWN) ? MOTION_BACKWARD : MOTION_NONE;
		break;
	case KEY_MOVE_BACKWARD:
		motionKeyStates.MoveBackward = KEYSTATE_UP;
		keyboardMotion.Surge = (motionKeyStates.MoveForward == KEYSTATE_DOWN) ? MOTION_FORWARD : MOTION_NONE;
		break;
	case KEY_MOVE_LEFT:
		motionKeyStates.MoveLeft = KEYSTATE_UP;
		keyboardMotion.Sway = (motionKeyStates.MoveRight == KEYSTATE_DOWN) ? MOTION_RIGHT : MOTION_NONE;
		break;
	case KEY_MOVE_RIGHT:
		motionKeyStates.MoveRight = KEYSTATE_UP;
		keyboardMotion.Sway = (motionKeyStates.MoveLeft == KEYSTATE_DOWN) ? MOTION_LEFT : MOTION_NONE;
		break;

		/*
		*	I AM CHANGING THE SECTION HAHAHAHA
		*/
	case KEY_TILT_UP:
		camKeyStates.TiltUp = KEYSTATE_UP;
		keyboardCameraMotion.Tilt = (camKeyStates.TiltUp == KEYSTATE_DOWN) ? MOTION_LOOK_UP : MOTION_NONE;
		break;
	case KEY_TILT_DOWN:
		camKeyStates.TiltDown = KEYSTATE_UP;
		keyboardCameraMotion.Tilt = (camKeyStates.TiltDown == KEYSTATE_DOWN) ? MOTION_LOOK_DOWN : MOTION_NONE;
		break;
	case KEY_ZOOM_IN:
		camKeyStates.ZoomIn = KEYSTATE_UP;
		keyboardCameraMotion.Zoom = (camKeyStates.ZoomIn == KEYSTATE_DOWN) ? MOTION_ZOOM_IN : MOTION_NONE;
		break;
	case KEY_ZOOM_OUT:
		camKeyStates.ZoomOut = KEYSTATE_UP;
		keyboardCameraMotion.Zoom = (camKeyStates.ZoomOut == KEYSTATE_DOWN) ? MOTION_ZOOM_OUT : MOTION_NONE;
		break;

		/*
			Other Keyboard Functions (add any new character key controls here)

			Note: If you only care when your key is first pressed down, you don't have to
			add anything here. You only need to put something in keyReleased if you care
			what happens when the user lets go, like we do with our movement keys above.
			For example: if you wanted a spotlight to come on while you held down "t", you
			would need to set a flag to turn the spotlight on in keyPressed, and update the
			flag to turn it off in keyReleased.
		*/
	}
}

/*
	Called each time a "special" key (e.g. an arrow key) is released.
*/
void specialKeyReleased(int key, int x, int y)
{
	switch (key) {
		/*
			Keyboard-Controlled Motion Handler - DON'T CHANGE THIS SECTION

			This works as per the motion keys in keyReleased.
		*/
	case SP_KEY_MOVE_UP:
		motionKeyStates.MoveUp = KEYSTATE_UP;
		keyboardMotion.Heave = (motionKeyStates.MoveDown == KEYSTATE_DOWN) ? MOTION_DOWN : MOTION_NONE;
		break;
	case SP_KEY_MOVE_DOWN:
		motionKeyStates.MoveDown = KEYSTATE_UP;
		keyboardMotion.Heave = (motionKeyStates.MoveUp == KEYSTATE_DOWN) ? MOTION_UP : MOTION_NONE;
		break;
	case SP_KEY_TURN_LEFT:
		motionKeyStates.TurnLeft = KEYSTATE_UP;
		keyboardMotion.Yaw = (motionKeyStates.TurnRight == KEYSTATE_DOWN) ? MOTION_CLOCKWISE : MOTION_NONE;
		break;
	case SP_KEY_TURN_RIGHT:
		motionKeyStates.TurnRight = KEYSTATE_UP;
		keyboardMotion.Yaw = (motionKeyStates.TurnLeft == KEYSTATE_DOWN) ? MOTION_ANTICLOCKWISE : MOTION_NONE;
		break;

		/*
			Other Keyboard Functions (add any new special key controls here)

			As per keyReleased, you only need to handle the key here if you want something
			to happen when the user lets go. If you just want something to happen when the
			key is first pressed, add you code to specialKeyPressed instead.
		*/
	}
}

/*
	Called by GLUT when it's not rendering a frame.

	Note: We use this to handle animation and timing. You shouldn't need to modify
	this callback at all. Instead, place your animation logic (e.g. moving or rotating
	things) within the think() method provided with this template.
*/
void idle(void)
{
	// Wait until it's time to render the next frame.

	unsigned int frameTimeElapsed = (unsigned int)glutGet(GLUT_ELAPSED_TIME) - frameStartTime;
	if (frameTimeElapsed < FRAME_TIME)
	{
		// This frame took less time to render than the ideal FRAME_TIME: we'll suspend this thread for the remaining time,
		// so we're not taking up the CPU until we need to render another frame.
		unsigned int timeLeft = FRAME_TIME - frameTimeElapsed;
		Sleep(timeLeft);
	}

	// Begin processing the next frame.

	frameStartTime = glutGet(GLUT_ELAPSED_TIME); // Record when we started work on the new frame.

	think(); // Update our simulated world before the next call to display().

	glutPostRedisplay(); // Tell OpenGL there's a new frame ready to be drawn.
}

/******************************************************************************
 * Animation-Specific Functions (Add your own functions at the end of this section)
 ******************************************************************************/

 /*
	 Initialise OpenGL and set up our scene before we begin the render loop.
 */
void init(void)
{
	// enable things
	glEnable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	fogger(); // enable fog

	// seed random
	srand(time(0));

	//glEnable(GL_TEXTURE_2D); // only call when drawing with textures. Textured objects should enable and disable this in their render functions.
	initLights();

	init_gameobjects();

	//glClearColor(0, 0.663, 0.937, 1.0); // Set the background colour to sky blue. #00A9EF
	glClearColor(0.98, 0.373, 0.333, 1.0); // set background colour to sunset orange #FA5F55
	// Anything that relies on lighting or specifies normals must be initialised after initLights.

	// Textures
	init_textures();

	// Display list
	displayList = init_displaylist();
	insert_displaylist(displayList, render_ground);
	insert_displaylist(displayList, render_sun);
	insert_displaylist(displayList, render_gigantic_gus_fring);
	insert_displaylist(displayList, render_road);

	// Render list 
	renderList = renderlist_init();
	init_cylinders();

	GameObject* bus = new_gameobject(render_bus, update_bus);
	bus->pos[2] = -40; // position bus on the road
	renderlist_push(renderList, bus);

	enemyCopter = new_gameobject(render_enemy_helicopter, 0); // fight disabled at start
	enemyCopter->pos[0] = 400;
	enemyCopter->pos[1] = 50;
	enemyCopter->pos[2] = 0;

	enemyCopter->rot[1] = 180; // face player's general direction
	renderlist_push(renderList, enemyCopter);
}

void init_gameobjects(void)
{
	c = new_camera();
	c->locked = 1; // lock camera at the start

	copter = new_gameobject(render_helicopter, 0);
	
	copter->pos[1] = 1; // set helicopter to sit on the ground
	copter->velocity = 0;
}

// define how dense the cylinders are
#define POSMAX 800
#define CYLINDER_COUNT 70
void init_cylinders(void)
{
	GLfloat pos[3];
	for (int i = 0; i < CYLINDER_COUNT; i++) // i is number of cylinders
	{
		pos[0] = randf() * POSMAX - (POSMAX / 2);
		pos[1] = 0;
		pos[2] = randf() * POSMAX - (POSMAX / 2);
		
		GameObject* cylinder = trollface_cylinder(pos);
		cylinder->rot[2] = rand() % 360;
		renderlist_push(renderList, cylinder);
	}
}

void fogger(void)
{
	glEnable(GL_FOG);

	GLfloat fogColor[4] = { 0.98, 0.373, 0.333, 1.0 };
	glFogi	(GL_FOG_MODE, GL_EXP2);
	glFogfv	(GL_FOG_COLOR, fogColor);
	glFogf	(GL_FOG_DENSITY, 0.003);
	glFogf	(GL_FOG_START, 7.0);
	glFogf	(GL_FOG_END, 20.0);
}
/*
	Advance our animation by FRAME_TIME milliseconds.

	Note: Our template's GLUT idle() callback calls this once before each new
	frame is drawn, EXCEPT the very first frame drawn after our application
	starts. Any setup required before the first frame is drawn should be placed
	in init().
*/

#define MOVESPEED 50
#define ROTSPEED 60
#define ZOOMSPEED 50
#define TILTSPEED 50

void think(void)
{
	// update the camera to stare at the controlled object
	c->set_target(c, copter->pos, copter->rot);
	c->update(c);
	
	// ppush new missile
	if (pushMissile)
	{
		renderlist_push(renderList, instantiate_missile(copter->pos, copter->rot));
		pushMissile = 0;
	}

	// update all interactive objects
	renderlist_update(renderList);

	/*
		Keyboard motion handler: complete this section to make your "player-controlled"
		object respond to keyboard input.
	*/
	// no fucking clue why it has to be -sin or -cos so i'm assuming it's just black magic
	float dx = MOVESPEED * FRAME_TIME_SEC * cos(rad(copter->rot[1]));
	float dz = MOVESPEED * FRAME_TIME_SEC * -sin(rad(copter->rot[1]));

	float dx2 = MOVESPEED * FRAME_TIME_SEC * -cos(rad(copter->rot[1] + 90));
	float dz2 = MOVESPEED * FRAME_TIME_SEC * sin(rad(copter->rot[1] + 90));

	if (keyboardMotion.Yaw != MOTION_NONE) 
	{
		/* TEMPLATE: Turn your object right (clockwise) if .Yaw < 0, or left (anticlockwise) if .Yaw > 0 */

		copter->rot[1] += keyboardMotion.Yaw * FRAME_TIME_SEC * ROTSPEED;
	}
	if (keyboardMotion.Surge != MOTION_NONE) 
	{
		/* TEMPLATE: Move your object backward if .Surge < 0, or forward if .Surge > 0 */

		copter->pos[0] += dx * keyboardMotion.Surge * FRAME_TIME_SEC * MOVESPEED;
		copter->pos[2] += dz * keyboardMotion.Surge * FRAME_TIME_SEC * MOVESPEED;
	}
	if (keyboardMotion.Sway != MOTION_NONE) 
	{
		/* TEMPLATE: Move (strafe) your object left if .Sway < 0, or right if .Sway > 0 */

		copter->pos[0] += dx2 * keyboardMotion.Sway * FRAME_TIME_SEC * MOVESPEED;
		copter->pos[2] += dz2 * keyboardMotion.Sway * FRAME_TIME_SEC * MOVESPEED;
	}
	if (keyboardMotion.Heave != MOTION_NONE) 
	{
		/* TEMPLATE: Move your object down if .Heave < 0, or up if .Heave > 0 */

		copter->pos[1] += keyboardMotion.Heave * FRAME_TIME_SEC * MOVESPEED;
		if (copter->pos[1] < 1 || copter->velocity < 800.0f)
		{
			copter->pos[1] = 1;
		}

		if (keyboardMotion.Heave > 0)
			copter->velocity += 200.0f * FRAME_TIME_SEC;
		else if (keyboardMotion.Heave < 0)
		{
			copter->velocity -= 200.0f * FRAME_TIME_SEC;
			if(copter->velocity < 0)
				copter->velocity = 0;
		}

	}

	// camera controls
	if (keyboardCameraMotion.Zoom != MOTION_NONE)
	{
		/* NOT A TEMPLATE: Zoom the camera in if .Zoom < 0, or out if .Zoom > 0 */
		c->dist += keyboardCameraMotion.Zoom * FRAME_TIME_SEC * ZOOMSPEED;
	}
	if (keyboardCameraMotion.Tilt != MOTION_NONE)
	{
		c->rot[0] += keyboardCameraMotion.Tilt * FRAME_TIME_SEC * TILTSPEED;
	}
}

/*
	Initialise OpenGL lighting before we begin the render loop.

	Note (advanced): If you're using dynamic lighting (e.g. lights that move around, turn on or
	off, or change colour) you may want to replace this with a drawLights function that gets called
	at the beginning of display() instead of init().
*/
void initLights(void)
{
	// Simple lighting setup
	GLfloat globalAmbient[] = { 0.98f * 0.4f, 0.373f * 0.4f, 0.333f * 0.4f, 1.0f };

	// Configure global ambient lighting.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	// Configure Light 0 as directional lighting (e.g. the sun).
	GLfloat lightPosition[] = { 1.0f, 0.5f, 1.0f, 0.0f };
	GLfloat ambientLight[] = { 0, 0, 0, 1 };
	GLfloat diffuseLight[] = { 1, 1, 1, 1 };
	GLfloat specularLight[] = { 1, 1, 1, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// LIGHT1 is for spotlight
	glEnable(GL_LIGHT1);
	glLighti(GL_LIGHT1, GL_SPOT_EXPONENT, 96); // smoothen out the spotlight

	// LIGHT2 is the bus light
	glEnable(GL_LIGHT2);
	glLighti(GL_LIGHT2, GL_SPOT_EXPONENT, 69);

	// Make GL normalize the normal vectors we supply.
	glEnable(GL_NORMALIZE);

	// Enable use of simple GL colours as materials.
	//glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
}

/******************************************************************************/