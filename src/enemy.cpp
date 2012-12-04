
#include <GL/gl.h>

#include "enemy.h"
#include "world.h"
#include "frand.h"

void enemy_system::init() {
	enemies.clear();
}

enemy& enemy_system::add_one() {
	enemies.push_back(enemy());
	return enemies.back();
}

void enemy_system::update(float time, world& w) {
	list<list<enemy>::iterator> todel;
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i) {
		i->update(time,w);
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

bool enemy_system::try_to_do_damage(vect missile_pos, float dmg, float fire) {
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i) 
		if(i->collides(missile_pos)) {
			i->accept_damage(dmg,fire);
			return true;
		}
	return false;
}

void enemy_system::finish() {
	enemies.clear();
}	

/* =========================================================== */

void enemy::update(float time, world& w) {
	switch (type) {
		case enemy_house:
			if(burning>0) {
				particle& p=w.ps.add_one();
				p.pos=pos+vect(DFRAND*size_x,DFRAND*size_y,size_z+FRAND*roof_size);
				p.spd=vect(DFRAND*0.2,DFRAND*0.2,2+FRAND);
				p.type=part_fire;
				p.life=1;
				p.r=1;
				p.g=FRAND/2;
				p.b=0.01;
				//TODO particle jednou za cas
			}
			break;
		case enemy_person:
			break;
		case enemy_tree: 
			break;
	}
	burning-=time;
	if(burning<0) burning=0;
	else hp-=time*5;
}

void enemy::draw() {
	float temp;
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	switch (type) {
		case enemy_house:
			glRotatef(rot,0,0,1);

			glBegin(GL_QUADS);
			if(burning>0) glColor3f(0.6,0.06,0);
			else glColor3f(0.8,0.1,0);
			
			temp=sqrt(roof_size*roof_size+size_y*size_y);

			glNormal3f(-roof_size/temp,0,size_y/(2*temp));
			glVertex3f(-size_x,-size_y,size_z);
			glVertex3f(size_x,-size_y,size_z);
			glVertex3f(size_x,0,size_z+roof_size);
			glVertex3f(-size_x,0,size_z+roof_size);
			
			glNormal3f(roof_size/temp,0,size_y/(2*temp));
			glVertex3f(-size_x,0,size_z+roof_size);
			glVertex3f(size_x,0,size_z+roof_size);
			glVertex3f(size_x,size_y,size_z);
			glVertex3f(-size_x,size_y,size_z);

			if(burning>0) glColor3f(0.8,0.8,0.8);
			else glColor3f(1,1,1);
			
			glNormal3f(0,-1,0);
			glVertex3f(-size_x,-size_y,0);
			glVertex3f(size_x,-size_y,0);
			glVertex3f(size_x,-size_y,size_z);
			glVertex3f(-size_x,-size_y,size_z);
			
			glNormal3f(0,1,0);
			glVertex3f(-size_x,size_y,0);
			glVertex3f(-size_x,size_y,size_z);
			glVertex3f(size_x,size_y,size_z);
			glVertex3f(size_x,size_y,0);
			
			glEnd();

			glBegin(GL_POLYGON);
			
			glNormal3f(-1,0,0);
			glVertex3f(-size_x,-size_y,0);
			glVertex3f(-size_x,-size_y,size_z);
			glVertex3f(-size_x,0,size_z+roof_size);
			glVertex3f(-size_x,size_y,size_z);
			glVertex3f(-size_x,size_y,0);
			
			glEnd();

			glBegin(GL_POLYGON);
			
			glNormal3f(1,0,0);
			glVertex3f(size_x,-size_y,0);
			glVertex3f(size_x,size_y,0);
			glVertex3f(size_x,size_y,size_z);
			glVertex3f(size_x,0,size_z+roof_size);
			glVertex3f(size_x,-size_y,size_z);
			
			glEnd();
		
			break;
		case enemy_person:
			break;
		case enemy_tree:
			break;
	}
	glPopMatrix();
}

void enemy::accept_damage(float dmg, float fire) {
	hp-=dmg;
	burning+=fire;
}

#define max(a,b) (((a)>(b))?(a):(b))

bool enemy::collides(vect missile_pos) {
	if((pos-missile_pos).length() < 0.7*max(max(size_x,size_y),size_z+roof_size)) return true;
	return false;
}

bool enemy::deletable() {
	if(hp<0) return true;
	return false;
}

