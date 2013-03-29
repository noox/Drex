
#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <GL/gl.h>
#include <vector>

using namespace std;

class world;
class game;

bool imageloader_init();
void imageloader_end();
GLuint imageloader_load (const char* fn, int BPP, GLuint type);
void imageloader_load_map (const char* fn, vector<int> &h, game& g, world& w);
bool imageloader_load_heightmap (vector<int> &h, int &size_x, int &size_y);
bool imageloader_load_color (const char* water, const char* lowland, const char* upland, const char* mountain, const char* ice, vector<unsigned char> &c, vector<int> h, game& g);
void imageloader_free (GLuint t);

#endif

