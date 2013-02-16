
#include <GL/gl.h>
#include <GL/glu.h>

#include "health.h"
#include "vector.h"
#include "world.h"

#include <iostream>
using namespace std;

void make_healthstatus(float timediff, world &w) {
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,800,600,0,-1,1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_BLEND);
	glColor4f(0.5,0.5,0.5,0.2);
	glBegin(GL_QUADS);
	glVertex2f(50,50);
	glVertex2f(50,100);
	glVertex2f(100,100);
	glVertex2f(100,50);
	glEnd();
	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}
