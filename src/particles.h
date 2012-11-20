
#include <list>

using namespace std;

#include "vector.h"

class particle {
public:
	vect pos, spd;
	int type;
	float r, g, b, life, age;

	particle() {}

	void update(float time);
	void draw();
};

class particle_system {
public:
	list<particle> particles;

	void init();
	particle& add_one();
	void update(float time);
	void draw();
	void finish();
};

