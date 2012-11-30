
#include <GL/gl.h>

#include "enemy.h"

void enemy_system::init() {
	enemies.clear();
}

enemy& enemy_system::add_one() {
	enemies.push_back(enemy());
	return enemies.back();
}

void enemy_system::update(float time) {
	list<list<enemy>::iterator> todel;
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i) {
		i->update(time);
		if(i->deletable()) todel.push_back(i);
	}
	while(!todel.empty()) {
		enemies.erase(todel.front());
		todel.pop_front();
	}	
}

void enemy_system::draw() {
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i)
		i->draw();
}

void enemy_system::finish() {
	enemies.clear();
}	

/* =========================================================== */

void enemy::update(float time) {
	switch (type) {
		case enemy_house:
			break;
		case enemy_person:
			break;
		case enemy_tree: 
			break;
	}
}

void enemy::draw() {
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glColor3f(0.3,0.3,0.3);
	switch (type) {
		case enemy_house:
			glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(1,0,0);
			glVertex3f(1,1,0);
			glVertex3f(0,1,0);

			glVertex3f(1,0,0);
			glVertex3f(1,0,2);
			glVertex3f(1,1,2);
			glVertex3f(1,1,0);
			
			glVertex3f(1,0,2);
			glVertex3f(0,0,2);
			glVertex3f(0,1,2);
			glVertex3f(1,1,2);
			
			glVertex3f(0,0,0);
			glVertex3f(0,1,0);
			glVertex3f(0,1,2);
			glVertex3f(0,0,2);
			
			glColor3f(1,0.3,0);
			glVertex3f(0,1,0);
			glVertex3f(1,1,0);
			glVertex3f(1,1,2);
			glVertex3f(0,1,2);
			glEnd();
			break;
		case enemy_person:
			break;
		case enemy_tree:
			break;
	}
	glPopMatrix();
}

bool enemy::deletable() {
	if(hp<0) return true;
	return false;
}

