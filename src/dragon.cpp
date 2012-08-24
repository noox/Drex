
#include <GL/gl.h>
#include <math.h>

#include "dragon.h"

void dragon::update(int mouse_x,int mouse_y,bool space,float timediff) {
	if(space) spd-=ori.vecz()*timediff*5;
	
	mom+=ori*(0.03*quat(0,mouse_y/2,0,-mouse_x));
	
	pos+=spd*timediff;
	ori+=mom*timediff;
	ori.normalize();
	spd*=powf(0.5,timediff);
	mom*=powf(0.2,timediff);
}

void dragon::draw() {
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	ori.gl_rotate();
	
	glBegin(GL_TRIANGLES);
	glColor3f(1,1,1);
	
	glVertex3f(1,0,0);
	glVertex3f(0,0.5,0);
	glVertex3f(-1,0,0);

	glVertex3f(1,0,0);
	glVertex3f(0,0,-3);
	glVertex3f(-1,0,0);

	glVertex3f(-1,0,0);
	glVertex3f(0,0.5,0);
	glVertex3f(0,0,-3);

	glVertex3f(1,0,0);
	glVertex3f(0,0,-3);
	glVertex3f(0,0.5,0);

	glEnd();
	glPopMatrix();
}

//vraci vhodou pozici kamery vuci drakovi
vect dragon::camera_pos() {
	return pos+ori.vecz()*10+ori.vecy()*3; 
}
