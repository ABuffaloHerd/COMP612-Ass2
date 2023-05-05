#include "Camera.h"
#include <stdio.h>
// fate/prototype
void update_camera(Camera* c);
Camera* new_camera(void);

// New camera
Camera* new_camera(void)
{
	Camera* c = (Camera*)malloc(sizeof(Camera));

	c->looking[0] = 0;
	c->looking[1] = 0;
	c->looking[2] = 0;

	c->pos[0] = 0;
	c->pos[1] = 0;
	c->pos[2] = 0;

	c->update = update_camera;

	return c;
}

// Update camera
void update_camera(Camera* c)
{
	printf("Camupdate\n");

	gluLookAt(c->pos[0], c->pos[1], c->pos[2], 
		c->looking[0], c->looking[1], c->looking[2],
		0, 1, 0);
}