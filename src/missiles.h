
#ifndef _MISSILE_H_
#define _MISSILE_H_

#include <list>

using namespace std;

#include "vector.h"

enum missile_type {
	missile_dragon_fire, 
	missile_dragon_ball
	//TODO enemies
};

class world;

class missile {
public:
	vect pos, spd;
	int type;
	float age, power, reload;
	bool deletable;

	missile() {
		age=0;
		deletable=false;
		reload=0;
	}

	void create();
	void update(float time, world& w);
	void draw();
};

class missile_system {
public:
	list<missile> missiles;

	void init();
	missile& add_one();
	void update(float time, world& w);
	void draw();
	void finish();
};

#endif

