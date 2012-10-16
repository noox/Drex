
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "game.h"

#include "imageloader.h"
#include "menu.h"

//status hry: 0 menu, 1 hra, 2 vitezstvi, 3 prohra

void game::init(){
	dr.set(vect(0,0,0),quat(1,0,0,0));
	cam.set(vect(0,0,0),quat(1,0,0,0));
	hm.load("data/hm3.png","data/color3.png");
	
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	
	glEnable(GL_DEPTH_TEST);
/*	texture=imageloader_load("data/hm.png");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
*/
	m.init();
	gamestatus=0;
}

void game::finish(){
	imageloader_free(texture);
}

bool game::update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y){
	switch (gamestatus){
		case 0:
			if(!m.update(timediff,esc_down,left_mouse_down,right_mouse_down,mouse_x,mouse_y)) return false;
			if(esc_down) return false;
			else return true;;
			return true;
			break;
		case 1:
			dr.update(mouse_x,mouse_y,space_down,timediff);
			cam.follow_ori(dr.ori,0.01,timediff);
			cam.follow_pos(dr.camera_pos(),0.3,timediff);
			if(esc_down) return false;
			else return true;
			break;
		case 2:
			break;
		case 3:
			break;
	}
}

float game::get_min_timediff(){
	return 0.02;
}

void game::render(){
	switch (gamestatus){
		case 0: 
			glDisable(GL_DEPTH_TEST);
			glClearColor(0,0,0,0);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0,800,0,600,1,-1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			m.render();
			glEnable(GL_DEPTH_TEST);
			break;
		case 1: 
			glClearColor(0,0,0,0);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(90,1.33333,0.1,1000);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			cam.set_gl();
			dr.draw();
			hm.draw();

			glColor3f(0.1,0.1,0.1);
			glPushMatrix();
			glScalef(10,10,10);
			glPopMatrix();
			break;
		case 2:
			break;
		case 3:
			break;
	}
}

