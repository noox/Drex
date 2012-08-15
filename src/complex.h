
#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <math.h>

class complex {
public:
	union {
		struct {
			float x,y;
		};
		float v[2];
	};

	complex() {
	}

	complex(float X, float Y) {
		x=X;
		y=Y;
	}
	
	const complex& operator=(const complex& a) {
		x=a.x;
		y=a.y;
		return *this;
	}

	const complex& operator+=(const complex& a) {
		x+=a.x;
		y+=a.y;
		return *this;
	}
	
	const complex& operator-=(const complex& a) {
		x-=a.x;
		y-=a.y;
		return *this;
	}
	
	const complex& operator*=(float a) {
		x*=a;
		y*=a;
		return *this;
	}
	
	const complex& operator/=(float a) {
		x/=a;
		y/=a;
		return *this;
	}
	
	const complex& operator*=(const complex& a) {
		*this=(*this)*a;
		return *this;
	}
	
	complex operator+(const complex& a) const {
		return complex(x+a.x,y+a.y);
	}
	
	complex operator-(const complex& a) const {
		return complex(x-a.x,y-a.y);
	}
	
	complex operator*(const complex& a) const {
		return complex(x*a.x-y*a.y,x*a.y+y*a.x);
	}

	complex operator*(float a) const {
		return complex(x*a,y*a);
	}

	complex operator/(float a) const {
		return complex(x/a,y/a);
	}

	float length() const {
		return sqrtf(x*x+y*y);
	}

	complex normal() const {
		return (*this)*(1/(this->length()));
	}
};

inline complex operator*(float a, const complex& b) {
	return b*a;
}

#endif

