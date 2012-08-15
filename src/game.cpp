
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "game.h"

void game::init(){
	dr.set(vect(0,0,0),quat(1,0,0,0));
	cam.set(vect(0,0,0),quat(1,0,0,0));
}

void game::finish(){
}

bool game::update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y){
	dr.update(mouse_x,mouse_y,space_down,timediff);
	cam.follow_ori(dr.ori,0.01,timediff);
	cam.follow_pos(dr.camera_pos(),0.3,timediff);
	if(esc_down) return false;
	else return true;
}

float game::get_min_timediff(){
	return 0.02;
}

void game::render(){
	glClearColor(0.3,0.3,1,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1.33333,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam.set_gl();
	dr.draw();

	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
	glScalef(10,10,10);
	glBegin(GL_LINES);
	for(int i=0;i<10;++i) for(int j=0;j<10;++j) {
		glVertex3f(0,i,j);glVertex3f(9,i,j);
	}
	for(int i=0;i<10;++i) for(int j=0;j<10;++j) {
		glVertex3f(i,0,j);glVertex3f(i,9,j);
	}
	for(int i=0;i<10;++i) for(int j=0;j<10;++j) {
		glVertex3f(i,j,0);glVertex3f(i,j,9);
	}
	glEnd();
	glPopMatrix();
}
