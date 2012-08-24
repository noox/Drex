
#include <GL/gl.h>

#include "imageloader.h"
#include "heightmap.h"

void heightmap::draw() {
	glColor3f(0.2,1,0.2);
	glBegin(GL_LINES);
	for(int i=0;i<size_y;++i)
		for(int j=0;j<size_x;++j) {
			glVertex3f(i,j,0.1*h[i*size_y+j]);
		}
	glEnd();
}

void heightmap::load(const char* fn) {
	free();
	imageloader_load_heightmap(fn,h,size_x,size_y);
}

void heightmap::free() {
	h.clear();
	size_x=0;
	size_y=0;
}
