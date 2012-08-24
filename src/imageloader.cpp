
#include <SDL/SDL_image.h>

#include <iostream>

using namespace std;

#include "imageloader.h"

bool imageloader_init() {
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if(initted&flags != flags) return false;
	else return true;
}

void imageloader_end() {
	IMG_Quit();
}

//loader textur
GLuint imageloader_load(const char* fn) {
	SDL_Surface *image;
	image = IMG_Load(fn);
	if(!image) return 0;
	GLuint t;
	glGenTextures(1,&t);
	glBindTexture(GL_TEXTURE_2D,t);
	glTexImage2D(GL_TEXTURE_2D,0,3,image->w,image->h,0,GL_RGB,
        	GL_UNSIGNED_BYTE,image->pixels);
	SDL_FreeSurface(image);
	return t;
}

bool imageloader_load_heightmap(const char* fn, vector<int> &h, int &size_x, int &size_y) {
	SDL_Surface *image;
	image = IMG_Load(fn);
	if(!image) return false;
	size_x = image->w;
	size_y = image->h;
	h.resize(size_x*size_y);
	for(int i=0;i<size_y;++i)
		for(int j=0;j<size_x;++j)
			h[i*size_y+j] = *((unsigned char*)image->pixels + i * image->pitch + j);
	SDL_FreeSurface(image);
	return true;
}

void imageloader_free(GLuint t) {
	glDeleteTextures(1,&t);
}
