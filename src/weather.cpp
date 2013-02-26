
#include "weather.h"
#include "particles.h"
#include "vector.h"
#include "frand.h"

#include <iostream>
using namespace std;

void make_rain (world &w) {
	vect a = w.dr.pos;
	//dest okolo draka
	{
		particle& p = w.ps.add_one();
		p.pos = vect (10 * DFRAND + a.x, 10 * DFRAND + a.y, 10 * DFRAND + a.z);
		p.spd = vect (0, 0, -1);
		p.type = part_rain;
		p.life = 5;
		p.r = 0;
		p.g = 0.2;
		p.b = 0.4;
	};
	//dest v pozadi
	{
		particle& p = w.ps.add_one();
		p.pos = vect (20 * DFRAND + a.x, 20 * DFRAND + a.y, 20 * DFRAND + a.z);
		p.spd = vect (0, 0, -1);
		p.type = part_rain;
		p.life = 3;
		p.r = 0;
		p.g = 0.2;
		p.b = 0.4;
	};
}

void make_snow (world &w) {
	vect a = w.dr.pos;
	//snih okolo draka
	{
		particle& p = w.ps.add_one();
		p.pos = vect (15 * DFRAND + a.x, 15 * DFRAND + a.y, 15 * DFRAND + a.z);
		p.spd = vect (DFRAND * 0.1, DFRAND * 0.1, -1);
		p.type = part_snow;
		p.life = 10;
		p.r = 0.1;
		p.g = 0.4;
		p.b = 0.4;
	};
	//snih v pozadi
	{
		particle& p = w.ps.add_one();
		p.pos = vect (25 * DFRAND + a.x, 25 * DFRAND + a.y, 25 * DFRAND + a.z);
		p.spd = vect (DFRAND * 0.1, DFRAND * 0.1, -1);
		p.type = part_snow;
		p.life = 3;
		p.r = 0.1;
		p.g = 0.4;
		p.b = 0.4;
	};
}

