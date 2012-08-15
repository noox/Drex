
#include "vector.h"
#include "quaternion.h"

class dragon {
public:
	vect pos,spd;
	quat ori,mom;

	void set(const vect &Pos,const quat &Ori) {
		pos=Pos;
		ori=Ori;
		ori.normalize();
		spd=vect(0,0,0);
		mom=quat(0,0,0,0);
	}

	void update(int mouse_x,int mouse_y,bool space,float timediff);
	void draw();
	vect camera_pos();
};