
#include "vector.h"
#include "quaternion.h"
#include "heightmap.h"

class dragon {
public:
	vect pos,spd;
	quat ori,mom;
	GLuint texture;

	void set(const vect &Pos,const quat &Ori) {
		pos=Pos;
		ori=Ori;
		ori.normalize();
		spd=vect(0,0,0);
		mom=quat(0,0,0,0);
	}

	void init();
	void update(int mouse_x,int mouse_y,bool space,float timediff,heightmap &hm);
	void draw();
	vect camera_pos();
	void finish();
};
