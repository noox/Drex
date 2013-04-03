
#include <GL/gl.h>

#include "vector.h"
#include "skybox.h"
#include "imageloader.h"

void skybox::init()
{
	sky = imageloader_load("data/skybox.png", 3, GL_RGB);
	glBindTexture(GL_TEXTURE_2D, sky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void skybox::draw(vect pos, bool night)
{
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sky);

	float bottom_color[] = {0.7, 0.8, 0.9};
	float top_color[] = {0.1, 0.4, 1};

	if (night) {
		bottom_color[0] = 0;
		bottom_color[1] = 0.3;
		bottom_color[2] = 1;
		top_color[0] = 0.2;
		top_color[1] = 0.2;
		top_color[2] = 0.2;
	}

	//spodni cast
	glBegin(GL_QUADS);
	glColor3fv(bottom_color);
	glTexCoord2f(0.5, 1);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0.25, 1);
	glVertex3f(1, -1, -1);
	glTexCoord2f(0.25, 0.6666666666666666);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0.5, 0.6666666666666666);
	glVertex3f(-1, 1, -1);

	//horni cast
	glColor3fv(top_color);
	glTexCoord2f(0.25, 0);
	glVertex3f(1, -1, 1);
	glTexCoord2f(0.5, 0);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(0.5, 0.3333333333333333);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0.25, 0.3333333333333333);
	glVertex3f(1, 1, 1);

	//1
	glColor3fv(top_color);
	glTexCoord2f(0, 0.3333333333333333);
	glVertex3f(1, -1, 1);
	glTexCoord2f(0.25, 0.3333333333333333);
	glVertex3f(1, 1, 1);
	glColor3fv(bottom_color);
	glTexCoord2f(0.25, 0.6666666666666666);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0, 0.6666666666666666);
	glVertex3f(1, -1, -1);

	//3
	glColor3fv(bottom_color);
	glTexCoord2f(0.75, 0.6666666666666666);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0.5, 0.6666666666666666);
	glVertex3f(-1, 1, -1);
	glColor3fv(top_color);
	glTexCoord2f(0.5, 0.3333333333333333);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0.75, 0.3333333333333333);
	glVertex3f(-1, -1, 1);

	//2
	glColor3fv(bottom_color);
	glTexCoord2f(0.5, 0.6666666666666666);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0.25, 0.6666666666666666);
	glVertex3f(1, 1, -1);
	glColor3fv(top_color);
	glTexCoord2f(0.25, 0.3333333333333333);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0.5, 0.3333333333333333);
	glVertex3f(-1, 1, 1);

	//4
	glColor3fv(top_color);
	glTexCoord2f(0.75, 0.3333333333333333);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(1, 0.3333333333333333);
	glVertex3f(1, -1, 1);
	glColor3fv(bottom_color);
	glTexCoord2f(1, 0.6666666666666666);
	glVertex3f(1, -1, -1);
	glTexCoord2f(0.75, 0.6666666666666666);
	glVertex3f(-1, -1, -1);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glDepthMask(true);
	glEnable(GL_DEPTH_TEST);
}

void skybox::finish()
{
	imageloader_free(sky);
}

