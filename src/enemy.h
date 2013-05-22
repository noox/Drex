
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <list>

using namespace std;

class world;

#include "vector.h"

class enemy
{
public:
	vect pos;
	float hp, reload;
	float size_x, size_y, size_z, roof_size, rot;
	bool noise;

	enemy() {
		reload = 0;
		hp = 20;
		noise = false;
	}

	void create();
	void update(float time, world& w);
	void draw(GLuint tex_wall, GLuint tex_red_roof, GLuint tex_black_roof,
	          GLuint tex_snowy_roof, GLuint tex_burning_roof, world& w);
	void accept_damage(float dmg);
	bool collides(vect missile_pos);
	bool deletable();
};

class enemy_system
{
public:
	list<enemy> enemies;
	GLuint tex_wall, tex_red_roof, tex_black_roof, tex_snowy_roof,
		tex_burning_roof;

	void init();
	enemy& add_one();
	void update(float time, world& w);
	void draw(world& w);
	bool try_to_damage_enemy(vect missile_pos, float dmg);
	void finish();
	bool all_enemies_dead();
	vect one_enemy();
};

#endif

