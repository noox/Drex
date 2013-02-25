
#include "weather.h"
#include "particles.h"
#include "vector.h"
#include "frand.h"

#include <iostream>
using namespace std;

void make_rain(world &w) {
	vect a=w.dr.pos;
	{particle& p=w.ps.add_one();
	p.pos=vect(10*DFRAND+a.x,10*DFRAND+a.y,10*DFRAND+a.z);
	p.spd=vect(0,0,-1);
	p.type=part_rain;
	p.life=5;
	p.r=0;
	p.g=0.1;
	p.b=0.3;
	};
}

void make_snow(world &w) {
}

