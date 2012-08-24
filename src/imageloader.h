
#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <GL/gl.h>
#include <vector>

bool imageloader_init();
void imageloader_end();
GLuint imageloader_load(const char* fn);
void imageloader_free(GLuint t);

#endif

