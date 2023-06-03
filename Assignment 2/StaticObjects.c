#include "StaticObjects.h"

extern GameObject* copter;
extern const float FRAME_TIME_SEC;

void render_cylinder(GameObject* cylinder);
void update_cylinder(GameObject* cylinder);

void render_gigantic_gus_fring(void)
{
	reset_material_properties();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	bind_texture(TEXTURE_FRING);

	glTranslatef(100.0f, 50.0f, 0.0f);

	// rotate to face cam
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(180, 0, 1, 0);

	glBegin(GL_QUADS);
	// top right
	glNormal3f(0, 1, 0);
	glTexCoord2i(TOPRIGHT);
	glVertex3f(50.0f, 0.0f, 10.0f);

	// top left
	glNormal3f(0, 1, 0);
	glTexCoord2i(TOPLEFT);
	glVertex3f(-50.0f, 0.0f, 10.0f);

	// bottom left
	glNormal3f(0, 1, 0);
	glTexCoord2i(BOTTOMLEFT);
	glVertex3f(-50.0f, 0.0f, -10.0f);

	// bottom right
	glNormal3f(0, 1, 0);
	glTexCoord2i(BOTTOMRIGHT);
	glVertex3f(50.0f, 0.0f, -10.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void render_sun(void)
{
	reset_material_properties();

	glDisable(GL_FOG); // this magic trick only works if fog is enabled, but makes the sun fully visible
	glPushMatrix();

	GLfloat sun_color[] = { 1.0f, 0.8f, 0.0f, 1.0f };
	GLfloat emmission[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat sun_position[] = { 0.0f, 60.0f, 550.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sun_color);
	glMaterialfv(GL_FRONT, GL_EMISSION, emmission);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);

	glTranslatef(sun_position[0], sun_position[1], sun_position[2]);
	glutSolidSphere(25.0f, 20, 20);

	glPopMatrix();
	glEnable(GL_FOG);
}

GameObject* trollface_cylinder(GLfloat pos[3])
{
	GameObject* obj = (GameObject*)malloc(sizeof(GameObject));

	obj->pos[0] = pos[0];
	obj->pos[1] = pos[1];
	obj->pos[2] = pos[2];

	obj->rot[0] = -90;
	obj->rot[1] = 0;
	// adjust z rotation to face upwards
	obj->rot[2] = 0;

	obj->timer = 0;
	obj->isTimed = 0;

	obj->update = update_cylinder;
	obj->render = render_cylinder;
}

void update_cylinder(GameObject* cylinder)
{
	cylinder->rot[2] += 10.0f * FRAME_TIME_SEC;
}

#define CYLINDER_HEIGHT 8
#define CYLINDER_RADIUS 4

void render_cylinder(GameObject* cylinder)
{
	// create quadric object
	GLUquadricObj* qobj = gluNewQuadric();

	// generate normals and texture coordinates
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);

	// set material properties to default
	reset_material_properties();

	// transformation push

	// bind texture
	glEnable(GL_TEXTURE_2D);

	bind_texture(TEXTURE_TROLL);

	// translate to position
	glPushMatrix();
	glTranslatef(cylinder->pos[0], cylinder->pos[1], cylinder->pos[2]);

	// rotate to orientation
	glRotatef(cylinder->rot[0], 1, 0, 0);
	glRotatef(cylinder->rot[1], 0, 1, 0);
	glRotatef(cylinder->rot[2], 0, 0, 1);

	// size is a hardcoded magic number (4 & 8)
	gluCylinder(qobj, CYLINDER_RADIUS, CYLINDER_RADIUS, CYLINDER_HEIGHT, 20, 20);

	// move to top of cylinder
	glTranslatef(0, 0, CYLINDER_HEIGHT);
	gluDisk(qobj, 0, CYLINDER_RADIUS, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(qobj);
}