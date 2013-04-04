
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "health.h"
#include "vector.h"

void make_healthstatus(world &w)
{
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glColor4f(0.5, 0.5, 0.5, 0.2);
	glBegin(GL_QUADS);
	glVertex2f(20, 20);
	glVertex2f(20, 580);
	glVertex2f(780, 580);
	glVertex2f(780, 20);
	glEnd();
	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

void make_dragon_hit() 
{
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glColor4f(1, 0.2, 0.2, 0.7);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 600);
	glVertex2f(800, 600);
	glVertex2f(800, 0);
	glEnd();
	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
}

