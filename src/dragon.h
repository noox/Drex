
#ifndef _DRAGON_H_
#define _DRAGON_H_

#include <GL/gl.h>

#include "vector.h"
#include "quaternion.h"

class world;

class dragon {
public:
	vect pos, spd;
	quat ori, mom;
	float hp;
	GLuint texture;
	float reload;
	int wings;

	void set (const vect &Pos, const quat &Ori) {
		pos = Pos;
		ori = Ori;
		ori.normalize();
		spd = vect (0, 0, 0);
		mom = quat (0, 0, 0, 0);
		reload = 0;
		hp = 1000;
	}

	void init();
	void update (int mouse_x, int mouse_y, bool left_mouse_down, bool right_mouse_down, bool space, float timediff, world &w);
	void draw();
	bool try_to_damage_dragon (vect missile_pos, float dmg);
	vect camera_pos();
	bool in_range (vect e_pos);
	bool collides (vect missile_pos);
	void accept_damage (float dmg);
	bool dead();
	void finish();
};

#endif

