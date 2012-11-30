
#include <list>

using namespace std;

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
	float hp;
	bool burning;

	enemy() {
		burning=false;
	}

	void create();
	void update(float time);
	void draw();
	bool deletable();
};

class enemy_system {
public:
	list<enemy> enemies;

	void init();
	enemy& add_one();
	void update(float time);
	void draw();
	void finish();
};

