
#include <list>

using namespace std;

#include "vector.h"

enum particle_type {
	part_fire,part_spark,part_smoke
};

class particle {
public:
	vect pos, spd;
	int type;
	float r, g, b, life, age;

	particle() {
		age=0;
	}

	void update(float time);
	void draw();
};

class particle_system {
public:
	list<particle> particles;
	GLuint tex_fire, tex_smoke;

	void init();
	particle& add_one();
	void update(float time);
	void draw();
	void finish();
};

