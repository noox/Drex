
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

class skybox {
public:
	GLuint sky;
	void draw (vect pos, bool night);
	void init();
	void finish();
};

#endif

