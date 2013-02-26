
#include <GL/gl.h>

#include "quaternion.h"

void quat::gl_rotate() {
	float m[4][4];
	vect t;
	t = vecx();
	m[0][0] = t.x;
	m[0][1] = t.y;
	m[0][2] = t.z;
	m[0][3] = 0;
	t = vecy();
	m[1][0] = t.x;
	m[1][1] = t.y;
	m[1][2] = t.z;
	m[1][3] = 0;
	t = vecz();
	m[2][0] = t.x;
	m[2][1] = t.y;
	m[2][2] = t.z;
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;

	glMultMatrixf (&m[0][0]);
}
