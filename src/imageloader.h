
#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <GL/gl.h>
#include <vector>

using namespace std;

bool imageloader_init();
void imageloader_end();
GLuint imageloader_load(const char* fn);
bool imageloader_load_heightmap(const char* fn, vector<int> &h, int &size_x, int &size_y);
void imageloader_free(GLuint t);

#endif
