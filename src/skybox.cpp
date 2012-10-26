
#include <GL/gl.h>

#include "vector.h"
#include "skybox.h"

void skybox::draw(vect pos) {
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);

	glColor3f(0.2,0.2,0.6);

	glBegin(GL_POLYGON);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,1,-1); 
	glVertex3f(1,1,-1);  
	glVertex3f(1,-1,-1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1,-1,1);
	glVertex3f(1,1,1);
	glVertex3f(-1,1,1);
	glVertex3f(-1,-1,1);
	glEnd();
	 
	glBegin(GL_POLYGON);
	glVertex3f(1,-1,-1);
	glVertex3f(1,1,-1);
	glVertex3f(1,1,1);
	glVertex3f(1,-1,1);
	glEnd();
	 
	glBegin(GL_POLYGON);
	glVertex3f(-1,-1,1);
	glVertex3f(-1,1,1);
	glVertex3f(-1,1,-1);
	glVertex3f(-1,-1,-1);
	glEnd();
	 
	glBegin(GL_POLYGON);
	glVertex3f(1,1,1);
	glVertex3f(1,1,-1);
	glVertex3f(-1,1,-1);
	glVertex3f(-1,1,1);
	glEnd();
	 
	glBegin(GL_POLYGON);
	glVertex3f(1,-1,-1);
	glVertex3f(1,-1,1);
	glVertex3f(-1,-1,1);
	glVertex3f(-1,-1,-1);
	glEnd();
 
	glPopMatrix();

	glDepthMask(true);
	glEnable(GL_DEPTH_TEST);
}

