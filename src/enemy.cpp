
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
	float temp;
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	switch (type) {
		case enemy_house:
			glRotatef(rot,0,0,1);

			glBegin(GL_QUADS);
			glColor3f(0.8,0.1,0);
			
			temp=sqrt(roof_size*roof_size+size_y*size_y/4);

			glNormal3f(-roof_size/temp,0,size_y/(2*temp));
			glVertex3f(0,0,size_z);
			glVertex3f(size_x,0,size_z);
			glVertex3f(size_x,size_y/2,size_z+roof_size);
			glVertex3f(0,size_y/2,size_z+roof_size);
			
			glNormal3f(roof_size/temp,0,size_y/(2*temp));
			glVertex3f(0,size_y/2,size_z+roof_size);
			glVertex3f(size_x,size_y/2,size_z+roof_size);
			glVertex3f(size_x,size_y,size_z);
			glVertex3f(0,size_y,size_z);

			glColor3f(1,1,1);
			glNormal3f(0,-1,0);
			glVertex3f(0,0,0);
			glVertex3f(size_x,0,0);
			glVertex3f(size_x,0,size_z);
			glVertex3f(0,0,size_z);
			
			glNormal3f(0,1,0);
			glVertex3f(0,size_y,0);
			glVertex3f(0,size_y,size_z);
			glVertex3f(size_x,size_y,size_z);
			glVertex3f(size_x,size_y,0);
			
			glEnd();

			glBegin(GL_POLYGON);
			
			glNormal3f(-1,0,0);
			glVertex3f(0,0,0);
			glVertex3f(0,0,size_z);
			glVertex3f(0,size_y/2,size_z+roof_size);
			glVertex3f(0,size_y,size_z);
			glVertex3f(0,size_y,0);
			
			glEnd();

			glBegin(GL_POLYGON);
			
			glNormal3f(1,0,0);
			glVertex3f(size_x,0,0);
			glVertex3f(size_x,size_y,0);
			glVertex3f(size_x,size_y,size_z);
			glVertex3f(size_x,size_y/2,size_z+roof_size);
			glVertex3f(size_x,0,size_z);
			
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

