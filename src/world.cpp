
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "game.h"

#include "imageloader.h"
#include "world.h"

//status hry: 0 menu, 1 hra, 2 vitezstvi, 3 prohra

void world::init(){
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
	glHint(GL_FOG_HINT,GL_NICEST);
	f.set_color(0.5,0.5,0.5);
	f.set_distance(50,150);
}

void world::finish(){
	imageloader_free(texture);
}

bool world::update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y){
	dr.update(mouse_x,mouse_y,space_down,timediff);
	cam.follow_ori(dr.ori,0.01,timediff);
	cam.follow_pos(dr.camera_pos(),0.3,timediff);
}

void world::render(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1.33333,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	cam.set_gl();
	skyb.draw(cam.pos);
	{
	float light_direction[]={0.4082,0.4082,0.8165,0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
	}
	f.turn_on();
	dr.draw();
	hm.draw();
	f.turn_off();

	glDisable(GL_LIGHTING);
}

