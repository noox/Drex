
#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include <vector>
#include <GL/gl.h>

using namespace std;

#include "vector.h"

class game;
class world;

class heightmap {
	vector<vect> normal;
	GLuint t, dl;
public:
	vector<int> h;
	vector<unsigned char> c;
	int size_x, size_y;
	void init (game& g, world& w);
	void draw();
	void load (const char* fn, game& g, world& w);
	float get_height (float x, float y);
	void get_sizes (float &x, float &y);
	void free();
	void finish();
};

#endif
