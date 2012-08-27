
#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include <vector>

using namespace std;

class heightmap {
public:
	vector<int> h;
	vector<unsigned char> c;
	int size_x, size_y;
	void draw();
	void load(const char* fn,const char* fn2);
	void free();
};

#endif
