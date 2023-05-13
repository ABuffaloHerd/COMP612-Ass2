#include "Camera.h"

inline double rad(double deg)
{
	return deg * (3.14159 / 180.0);
}

void set_target(Camera* c, GLfloat target[3], GLfloat targetrot[3])
{
	c->lock_target[0] = target[0];
	c->lock_target[1] = target[1];
	c->lock_target[2] = target[2];

	c->lock_target_rot[0] = targetrot[0];
	c->lock_target_rot[1] = targetrot[1];
	c->lock_target_rot[2] = targetrot[2];
}

void update_camera(Camera* c)
{
	// based of target, update camera position to be behind target. Camera is always looking at target.
	// however, apply rotations so that the camera can move around the target
	// if the camera is locked, then it stays behind, otherwise it can move around freely (staring at the target)
	// the display method will handle the looking, this function just needs to calculate the camera's position relative to the target

	// Camera's polar coordinates
	GLfloat r = c->dist; // Distance from the target
	GLfloat theta = rad(c->rot[1]); // yaw
	GLfloat phi = rad(c->rot[0]); // pitch

	// Convert polar coordinates to Cartesian coordinates
	float x = r * sin(theta);
	float z = r * cos(theta);
	float y = r * sin(phi);
	c->pos[0] = c->lock_target[0] + x;
	c->pos[1] = c->lock_target[1] + y;
	c->pos[2] = c->lock_target[2] + z;

	// If the camera is locked, set the pitch and yaw angles to set values
	if (c->locked)
	{
		c->rot[0] = 30.0f; // Pitch
		c->rot[1] = c->lock_target_rot[1] - 90; // Yaw
	}

	//printf("Camera lockon target: %f, %f, %f ", c->lock_target[0], c->lock_target[1], c->lock_target[2]);
}

Camera* new_camera(void)
{
	Camera* c = (Camera*)malloc(sizeof(Camera));

	c->pos[0] = 5;
	c->pos[1] = 5;
	c->pos[2] = 5;

	c->rot[0] = 0;
	c->rot[1] = 0;
	c->rot[2] = 0;

	c->locked = 0;
	c->dist = 18;

	c->update = update_camera;
	c->set_target = set_target;
}