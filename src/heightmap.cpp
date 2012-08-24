
#include <GL/gl.h>

#include "imageloader.h"
#include "heightmap.h"

#define hm_vertex(x,y) glColor3ub(16,h[y*size_y+x],16); glVertex3f(y,x,0.1*h[y*size_y+x]);

void heightmap::draw() {
	for(int i=0;i<size_y;++i) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int j=0;j<size_x;++j) {
			hm_vertex(i+1,j)
			hm_vertex(i,j)
		}
		glEnd();
	}
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
