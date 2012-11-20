
#include <GL/gl.h>

#include "missiles.h"

void missile_system::init() {
	missiles.clear();
}

missile& missile_system::add_one() {
	missiles.push_back(missile());
	return missiles.back();
}

void missile_system::update(float time) {
	list<list<missile>::iterator> todel;
	for(list<missile>::iterator i=missiles.begin();i!=missiles.end();++i) {
		i->update(time);
		if(i->deletable) todel.push_back(i);
	}
	while(!todel.empty()) {
		missiles.erase(todel.front());
		todel.pop_front();
	}	
}

void missile_system::draw() {
	for(list<missile>::iterator i=missiles.begin();i!=missiles.end();++i)
		i->draw();
}

void missile_system::finish() {
	missiles.clear();
}	

/* =========================================================== */

void missile::update(float time) {
	switch (type) {
		case 0:
			break;
		case 1:
			break;
		default: 
			break;
	}
}

void missile::draw() {
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glColor3f(1,1,1);
	glPopMatrix();
}


