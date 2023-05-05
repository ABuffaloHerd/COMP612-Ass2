#include "Camera.h"

void update_freecam(Camera* c);

inline double rad(double deg)
{
	return deg * (3.14159 / 180.0);
}

void set_target(Camera* c, GLfloat target[3])
{
	c->lock_target[0] = target[0];
	c->lock_target[1] = target[1];
	c->lock_target[2] = target[2];
}

void update_camera(Camera* c)
{
	if (c->locked)
	{
		// locked update
	}
	else
	{
		// freecam update
		update_freecam(c);
	}
}

void update_freecam(Camera* c)
{
	// update the camera position (entire world) using the transform matrix

	glRotatef(c->rot[0], 1, 0, 0);
	glRotatef(c->rot[1], 0, 1, 0);
	glRotatef(0, 0, 0, 1);
	glTranslatef(c->pos[0], c->pos[1], c->pos[2]);


	printf("%f, %f, %f\n", c->pos[0], c->pos[1], c->pos[2]);
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
	c->dist = 4;

	c->update = update_camera;
	c->set_target = set_target;
}