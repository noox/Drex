
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <list>

using namespace std;

class world;

#include "vector.h"

enum enemy_type {
	enemy_house,
	enemy_person,
	enemy_tree
};

class enemy {
public:
	vect pos, spd;
	int type;
	float hp, burning;

	//vlastnosti domu
	float size_x, size_y, size_z, roof_size, rot;

	enemy() {
		burning=0;
	}

	void create();
	void update(float time, world& w);
	void draw();
	void accept_damage(float dmg, float fire);
	bool collides(vect missile_pos);
	bool deletable();
};

class enemy_system {
public:
	list<enemy> enemies;

	void init();
	enemy& add_one();
	void update(float time, world& w);
	void draw();
	bool try_to_do_damage(vect missile_pos, float dmg, float fire);
	void finish();
	bool all_enemies_dead();
};

#endif

