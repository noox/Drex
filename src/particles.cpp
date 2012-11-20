
#include <GL/gl.h>

#include "particles.h"

void particle_system::init() {
	particles.clear();
}

particle& particle_system::add_one() {
	particles.push_back(particle());
	return particles.back();
}

void particle_system::update(float time) {
	list<list<particle>::iterator> todel;
	for(list<particle>::iterator i=particles.begin();i!=particles.end();++i) {
		i->update(time);
		if(i->age > i->life) todel.push_back(i);
	}
	while(!todel.empty()) {
		particles.erase(todel.front());
		todel.pop_front();
	}	
}

void particle_system::draw() {
	for(list<particle>::iterator i=particles.begin();i!=particles.end();++i)
		i->draw();
}

void particle_system::finish() {
	particles.clear();
}	

/* =========================================================== */

void particle::update(float time) {
	switch (type) {
		case 0:
			break;
		case 1:
			break;
		default: 
			break;
	}
}

void particle::draw() {
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glColor3f(1,1,1);
	glPopMatrix();
}

