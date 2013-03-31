
#ifndef _VECT_H_
#define _VECT_H_

#include <math.h>

class vect
{
public:
	union {
		struct {
			float x, y, z;
		};
		float v[3];
	};

	vect() {
	}

	vect(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}

	const vect& operator= (const vect& a) {
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	const vect& operator+= (const vect& a) {
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	const vect& operator-= (const vect& a) {
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	const vect& operator*= (float a) {
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	const vect& operator/= (float a) {
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

	vect operator+ (const vect& a) const {
		return vect(x + a.x, y + a.y, z + a.z);
	}

	vect operator- (const vect& a) const {
		return vect(x - a.x, y - a.y, z - a.z);
	}

	vect operator*(float a) const {
		return vect(x * a, y * a, z * a);
	}

	//skalarni soucin
	float operator% (const vect& a) const {
		return x * a.x + y * a.y + z * a.z;
	}

	//vektorovy soucin
	vect operator^(const vect& a) const {
		return vect(y * a.z - z * a.y, z * a.x - x * a.z, 
			x * a.y - y * a.x);
	}

	vect operator/ (float a) const {
		return vect(x / a, y / a, z / a);
	}

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	vect normal() const {
		return (*this) * (1 / (this->length()));
	}

	vect unit() const {
		return (*this) / length();
	}

	vect operator| (const float& size) const {
		return unit() * size;
	}
};

inline vect operator*(float a, const vect& b)
{
	return b * a;
}

#endif

