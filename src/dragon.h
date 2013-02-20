
#ifndef _DRAGON_H_
#define _DRAGON_H_

#include <GL/gl.h>

#include "vector.h"
#include "quaternion.h"

class world;

class dragon {
public:
	vect pos,spd;
	quat ori,mom;
	GLuint texture;
	float reload;
	int wings;

	void set(const vect &Pos,const quat &Ori) {
		pos=Pos;
		ori=Ori;
		ori.normalize();
		spd=vect(0,0,0);
		mom=quat(0,0,0,0);
		reload=0;
	}

	void init();
	void update(int mouse_x,int mouse_y,bool left_mouse_down,bool right_mouse_down,bool space,float timediff,world &w);
	void draw();
	vect camera_pos();
	void finish();
};

#endif

