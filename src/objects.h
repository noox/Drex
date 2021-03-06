
#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <list>

using namespace std;

class world;

#include "vector.h"
#include "frand.h"

enum object_type {
	object_person,
	object_tree1,
	object_tree2,
	object_tree3
};

class object
{
public:
	vect pos, spd;
	int type;
	float size, hp, reload;
	vect start_pos;

	object() {
		reload = 0;
	}

	void create();
	void update(float time, world& w);
	void draw(GLuint tex_tree1, GLuint tex_tree2, GLuint tex_tree3,
		GLuint tex_snowy_tree2, GLuint tex_snowy_tree3,
	        GLuint tex_person, world &w);
	void accept_damage(float dmg);
	bool collides(vect missile_pos);
	bool deletable();
};

class object_system
{
public:
	list<object> objects;
	GLuint tex_tree1, tex_tree2, tex_tree3, tex_snowy_tree2, 
		tex_snowy_tree3, tex_person;

	void init();
	object& add_one();
	void update(float time, world& w);
	void draw(world &w);
	bool try_to_damage_object(vect missile_pos, float dmg);
	void finish();
	void delete_object(int x);
};

#endif

