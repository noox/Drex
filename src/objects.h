
#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <list>

using namespace std;

class world;

#include "vector.h"

enum object_type {
	object_person,
	object_shooting_person,
	object_tree
};

class object {
public:
	vect pos, spd;
	int type;
	float hp, burning, reload;

	//vlastnosti lidi
	float size_p;
	vect start_pos;
	//vlastnosti stromu
	float size_tr;

	object() {
		burning=0;
		reload=0;
	}

	void create();
	void update(float time, world& w);
	void draw();
	void accept_damage(float dmg, float fire);
	bool collides(vect missile_pos);
	bool deletable();
};

class object_system {
public:
	list<object> objects;

	void init();
	object& add_one();
	void update(float time, world& w);
	void draw();
	bool try_to_damage_object(vect missile_pos, float dmg, float fire);
	void finish();
	bool all_objects_dead();
};

#endif

