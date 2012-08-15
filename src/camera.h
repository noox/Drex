
#include "vector.h"
#include "quaternion.h"

class camera {
public:
	vect pos;
	quat ori;

	void set(const vect &Pos,const quat &Ori) {
		pos=Pos;
		ori=Ori;
	}
	void follow_pos(const vect &Pos,float speed,float timediff);
	void follow_ori(const quat &Ori,float speed,float timediff);
	void set_gl();
};

