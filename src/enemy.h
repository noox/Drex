
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <list>

using namespace std;

class world;

#include "vector.h"

class enemy {
public:
	vect pos;
	float hp, burning;
	float size_x, size_y, size_z, roof_size, rot;

	enemy() {
		burning = 0;
		hp = 100;
	}

	void create();
	void update (float time, world& w);
	void draw (GLuint tex_wall, GLuint tex_red_roof, GLuint tex_black_roof, GLuint tex_burning_roof);
	void accept_damage (float dmg, float fire);
	bool collides (vect missile_pos);
	bool deletable();
};

class enemy_system {
public:
	list<enemy> enemies;
	GLuint tex_wall, tex_red_roof, tex_black_roof, tex_burning_roof;

	void init();
	enemy& add_one();
	void update (float time, world& w);
	void draw();
	bool try_to_damage_enemy (vect missile_pos, float dmg, float fire);
	void finish();
	bool all_enemies_dead();
	vect one_enemy();
};

#endif

