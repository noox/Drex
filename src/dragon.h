
#ifndef _DRAGON_H_
#define _DRAGON_H_

#include <GL/gl.h>

#include "vector.h"
#include "quaternion.h"

class world;

class dragon
{
public:
	vect pos, spd;
	quat ori, mom;
	float hp, reload_dragon_fire, reload_dragon_ball;
	GLuint texture;
	int wings;

	void set(const vect &Pos, const quat &Ori) {
		pos = Pos;
		ori = Ori;
		ori.normalize();
		spd = vect(0, 0, 0);
		mom = quat(0, 0, 0, 0);
		reload_dragon_fire = -0.3;
		reload_dragon_ball = -5;
		hp = 100;
	}

	void init();
	void update(int mouse_x, int mouse_y, bool left_mouse_down,
	            bool right_mouse_down, bool space, float timediff, 
		    world &w);
	void draw();
	bool try_to_damage_dragon(vect missile_pos, float dmg, world& w);
	vect camera_pos();
	bool in_range(vect e_pos);
	bool collides(vect missile_pos);
	void accept_damage(float dmg);
	bool dead();
	float get_hp();
	void finish();
};

#endif

