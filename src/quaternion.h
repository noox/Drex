
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <math.h>
#include "vector.h"

class quat {
public:
	union {
		struct {
			float w,x,y,z;
		};
		float v[4];
	};

	quat() {
	}

	quat(float W, float X, float Y, float Z) {
		w=W;
		x=X;
		y=Y;
		z=Z;
	}

	quat(float angle, const vect& axis) {
		w=cosf(angle/2);
		float sine=sinf(angle/2);
		x=axis.x*sine;
		y=axis.y*sine;
		z=axis.z*sine;
	}
	
	const quat& operator=(const quat& a) {
		w=a.w;
		x=a.x;
		y=a.y;
		z=a.z;
		return *this;
	}

	const quat& operator*=(float a) {
		w*=a;
		x*=a;
		y*=a;
		z*=a;
		return *this;
	}
	
	const quat& operator/=(float a) {
		w/=a;
		x/=a;
		y/=a;
		z/=a;
		return *this;
	}
	
	const quat& operator*=(const quat& a) {
		*this=(*this)*a;
		return *this;
	}
	
	quat operator*(float a) const {
		return quat(w*a,x*a,y*a,z*a);
	}

	quat operator/(float a) const {
		return quat(w/a,x/a,y/a,z/a);
	}

	quat operator*(const quat& a) const {
		return quat(
			w*a.w-x*a.x-y*a.y-z*a.z,
			w*a.x+x*a.w+y*a.z-z*a.y,
			w*a.y-x*a.z+y*a.w+z*a.x,
			w*a.z+x*a.y-y*a.x+z*a.w);
	}

	float length() const {
		return sqrtf(w*w+x*x+y*y+z*z);
	}

	quat normal() const {
		return (*this)*(1/(this->length()));
	}
	
	vect vecx() const {
		return vect(w*w+x*x-y*y-z*z,
			2*x*y+2*w*z,
			2*x*z-2*w*y);
	}

	vect vecy() const {
		return vect(2*x*y-2*w*z,
			w*w-x*x+y*y-z*z,
			2*y*z+2*w*x);
	}

	vect vecz() const {
		return vect(2*x*z+2*w*y,
			2*y*z-2*w*x,
			w*w-x*x-y*y+z*z);
	}
};

inline quat operator*(float a, const quat& b) {
	return b*a;
}

#endif

