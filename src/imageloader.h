
#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <GL/gl.h>
#include <vector>

using namespace std;

bool imageloader_init();
void imageloader_end();
GLuint imageloader_load (const char* fn, int BPP, GLuint type);
bool imageloader_load_heightmap (const char* fn, vector<int> &h, int &size_x, int &size_y);
bool imageloader_load_color (const char* fn2, vector<unsigned char> &c, int size_x, int size_y);
void imageloader_free (GLuint t);

#endif

