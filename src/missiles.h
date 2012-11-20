
#include <list>

using namespace std;

#include "vector.h"

class missile {
public:
	vect pos, spd;
	int type;
	float age, power;
	bool deletable;

	missile() {}

	void create();
	void update(float time);
	void draw();
};

class missile_system {
public:
	list<missile> missiles;

	void init();
	missile& add_one();
	void update(float time);
	void draw();
	void finish();
};

