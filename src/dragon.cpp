
#include <GL/gl.h>
#include <math.h>

#include "vector.h"

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

	vect points[][2] = {
		// hlava
		{vect(0,19,0),vect(0,1,0)}, 
		{vect(1,19,0),vect(0.707,0.707,0)},
		{vect(0,17,1),vect(0,0,1)},
		{vect(2,17,0),vect(1,0,0)},
		{vect(1,16,0),vect(0.707,-0.707,0)},
		//telo
		{vect(1,13,0),vect(1,0,0)},
		{vect(0,11,1.5),vect(0,0,1)},
		{vect(2,11,0),vect(1,0,0)},
		{vect(2,8,0),vect(1,0,0)},
		{vect(0,7,1),vect(0,0,1)},
		{vect(1.5,7,0),vect(1,0,0)},
		//ocas
		{vect(0,4,0.5),vect(0,0,1)},
		{vect(0.5,4,0),vect(1,0,0)},
		{vect(0,0,0),vect(0,-1,0)},
		//kridlo
		{vect(5,12,0),vect(0,0,1)},
		{vect(8,11,0),vect(0,0,1)},
		{vect(10,9,0),vect(0,0,1)},
		{vect(4,8,0),vect(0,0,1)},
		{vect(7,8,0),vect(0,0,1)},
		{vect(11,6,0),vect(0,0,1)},
		//telo spodek = brisko
		{vect(0,17,-1),vect(0,0,-1)},
		{vect(0,11,-1.5),vect(0,0,-1)},
		{vect(0,7,-1),vect(0,0,-1)},
		{vect(0,4,-0.5),vect(0,0,-1)},

	};
	
#define point(x) glNormal3fv(points[x-1][1].v); glVertex3fv(points[x-1][0].v);

	glPushMatrix();
	glScalef(0.2,0.2,0.2);
	glRotatef(-90,1,0,0);
	glTranslatef(0,-10,0);
	glColor3f(0.2,0.5,0.1);
	//telo zprava shora
	glBegin(GL_TRIANGLE_FAN);
		point(3)
		point(7)
		point(6)
		point(5)
		point(4)
		point(2)
		point(1)
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
		point(7)
		point(10)
		point(11)
		point(9)
		point(8)
		point(6)
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		point(11)
		point(10)
		point(13)
		point(12)
		point(14)
	glEnd();
	//prave kridlo shora
	glBegin(GL_TRIANGLE_FAN);
		point(19)
		point(20)
		point(17)
		point(16)
		point(15)
		point(18)
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		point(9)
		point(18)
		point(8)
		point(15)
	glEnd();
	//telo zprava zdola
	glBegin(GL_TRIANGLE_FAN);
		point(21)
		point(1)
		point(2)
		point(4)
		point(5)
		point(6)
		point(22)
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
		point(22)
		point(6)
		point(8)
		point(9)
		point(11)
		point(23)
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		point(14)
		point(23)
		point(13)
		point(23)
		point(11)
	glEnd();
	//prave kridlo zdola
	glPushMatrix();
	glRotatef(180,0,1,0);
	glScalef(-1,1,1);
	glBegin(GL_TRIANGLE_FAN);
		point(19)
		point(18)
		point(15)
		point(16)
		point(17)
		point(20)
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		point(15)
		point(18)
		point(8)
		point(9)
	glEnd();
	glPopMatrix();

	glScalef(-1,1,1);

	//telo zleva shora
	glBegin(GL_TRIANGLE_FAN);
		point(3)
		point(1)
		point(2)
		point(4)
		point(5)
		point(6)
		point(7)
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
		point(7)
		point(6)
		point(8)
		point(9)
		point(11)
		point(10)
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		point(14)
		point(12)
		point(13)
		point(10)
		point(11)
	glEnd();
	//leve kridlo shora
	glBegin(GL_TRIANGLE_FAN);
		point(19)
		point(18)
		point(15)
		point(16)
		point(17)
		point(20)
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		point(15)
		point(18)
		point(8)
		point(9)
	glEnd();
	//telo zleva zdola
	glBegin(GL_TRIANGLE_FAN);
		point(21)
		point(22)
		point(6)
		point(5)
		point(4)
		point(2)
		point(1)
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
		point(22)
		point(23)
		point(11)
		point(9)
		point(8)
		point(6)
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		point(11)
		point(23)
		point(13)
		point(23)
		point(14)
	glEnd();
	//leve kridlo zdola
	glPushMatrix();
	glRotatef(180,0,1,0);
	glScalef(-1,1,1);
	glBegin(GL_TRIANGLE_FAN);
		point(19)
		point(20)
		point(17)
		point(16)
		point(15)
		point(18)
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		point(15)
		point(8)
		point(18)
		point(9)
	glEnd();
	glPopMatrix();

	glPopMatrix();
/*
	glBegin(GL_TRIANGLES);
	glColor3f(1,1,1);

	glNormal3f(0,0,1);
	glVertex3f(1,0,0);
	glVertex3f(0,0.5,0);
	glVertex3f(-1,0,0);

	glNormal3f(0,-1,0);
	glVertex3f(1,0,0);
	glVertex3f(0,0,-3);
	glVertex3f(-1,0,0);

	glNormal3f(-0.3,0.6,-0.1);
	glVertex3f(-1,0,0);
	glVertex3f(0,0.5,0);
	glVertex3f(0,0,-3);

	glNormal3f(0.3,0.6,-0.1);
	glVertex3f(1,0,0);
	glVertex3f(0,0,-3);
	glVertex3f(0,0.5,0);

	glEnd();
*/
	glPopMatrix();
}

//vraci vhodou pozici kamery vuci drakovi
vect dragon::camera_pos() {
	return pos+ori.vecz()*10+ori.vecy()*3; 
}
