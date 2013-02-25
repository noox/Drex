
#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include <list>

using namespace std;

#include "vector.h"

class world;

enum particle_type {
	part_fire,
	part_spark,
	part_smoke,
	part_rain
};

class particle_system;

class particle {
public:
	vect pos, spd;
	int type;
	float r, g, b, life, age;

	particle() {
		age=0;
	}

	void update(float time);
};

class particle_system {
public:
	list<particle> particles;
	GLuint tex_fire, tex_smoke;

	void init();
	particle& add_one();
	void update(float time);
	void draw(world &w);
	void finish();
};

#endif

