
#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include <vector>
#include <GL/gl.h>

#include "vector.h"

using namespace std;

class heightmap {
	vector<vect> normal;
	GLuint t;
public:
	vector<int> h;
	vector<unsigned char> c;
	int size_x, size_y;
	void init();
	void draw();
	void load(const char* fn,const char* fn2);
	float get_height(float x, float y);
	void free();
	void finish();
};

#endif
