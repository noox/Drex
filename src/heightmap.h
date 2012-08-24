
#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include <vector>

class heightmap {
public:
	vector<int> h;
	int size_x, size_y;
	void draw();
	void load(const char* fn);
	void free();
};

#endif
