
#include <iostream>
using namespace std;

#include <GL/gl.h>

#include "enemy.h"
#include "world.h"
#include "frand.h"

void enemy_system::init() {
	enemies.clear();
}

//pridani jednoho nepritele
enemy& enemy_system::add_one() {
	enemies.push_back(enemy());
	return enemies.back();
}

//update vsech nepratel v case
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

//nakresleni vsech nepratel v case
void enemy_system::draw() {
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i)
		i->draw();
}

//zajistuje kolize a ztratu hp nepratel
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

//funkce pro zjisteni zbytku nepratel - pro konec hry
bool enemy_system::all_enemies_dead() {
	if(enemies.empty()) return true;
	return false;
}
/* =========================================================== */

void enemy::update(float time, world& w) {
	float border;
	switch (type) {
		//domy
		case enemy_house:
			burning-=time;
			if(burning<0) burning=0;
			else hp-=time*5;

			if(burning>0) {
				//partikly pro horeni poskozenych domu
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

			if(deletable()) {
				//vybuch z partiklu, pokud dum ztrati hp
				for(int i=0;i<100;++i) {
					particle& p=w.ps.add_one();
					p.pos=pos;
					p.spd=vect(DFRAND,DFRAND,DFRAND).normal()*5;
					p.type=part_fire;
					p.life=1;
					p.r=1;
					p.g=FRAND/2;
					p.b=0.01;
					//TODO particle jednou za cas
					p=w.ps.add_one();
					p.pos=pos+vect(DFRAND,DFRAND,DFRAND)*3*FRAND;
					p.spd=vect(DFRAND,DFRAND,DFRAND).normal()*0.5;
					p.type=part_smoke;
					p.life=3;
					p.r=0.5;
					p.g=0.5;
					p.b=0.5;

				}
			}
			break;
		
		//lide
		case enemy_person:
			burning-=time;
			if(burning<0) burning=0;
			else hp-=time*5;
			
			//pohyb lidi
			pos+=spd*time;
			pos.z=w.hm.get_height(pos.x,pos.y);
			//hranice chuze pro lidi
			border=10*size_p;
			if(pos.x-start_pos.x >= border) {
				pos.x=start_pos.x+border;
				spd.x*=-1;
			}
			if(pos.x-start_pos.x <= -border) {
				pos.x=start_pos.x-border;
				spd.x*=-1;
			}
			if(pos.y-start_pos.y >= border) {
				pos.y=start_pos.y+border;
				spd.y*=-1;
			}
			if(pos.y-start_pos.y <= -border) {
				pos.y=start_pos.y-border;
				spd.y*=-1;
			}

			if(burning>0) {
				//partikly pro horeni poskozenych nepratel
				particle& p=w.ps.add_one();
				p.pos=pos*DFRAND*size_p;
				p.spd=vect(DFRAND*0.2,DFRAND*0.2,2+FRAND);
				p.type=part_fire;
				p.life=1;
				p.r=1;
				p.g=FRAND/2;
				p.b=0.01;
				//TODO particle jednou za cas
			}

			if(deletable()) {
				//vybuch z partiklu, pokud nepritel ztrati hp
				for(int i=0;i<100;++i) {
					particle& p=w.ps.add_one();
					p.pos=pos;
					p.spd=vect(DFRAND,DFRAND,DFRAND).normal()*5;
					p.type=part_fire;
					p.life=1;
					p.r=1;
					p.g=0;
					p.b=0;
					//TODO particle jednou za cas
					p=w.ps.add_one();
					p.pos=pos+vect(DFRAND,DFRAND,DFRAND);
					p.spd=vect(DFRAND,DFRAND,DFRAND).normal()*0.5;
					p.type=part_smoke;
					p.life=3;
					p.r=1;
					p.g=0;
					p.b=0;

				}
			}
			break;
	
		//stromy
		case enemy_tree: 
			burning-=time;
			if(burning<0) burning=0;
			else hp-=time*5;

			if(burning>0) {
				//partikly pro horeni poskozenych stromu
				particle& p=w.ps.add_one();
				p.pos=pos*DFRAND*size_tr;
				p.spd=vect(DFRAND*0.2,DFRAND*0.2,2+FRAND);
				p.type=part_fire;
				p.life=1;
				p.r=1;
				p.g=FRAND/2;
				p.b=0.01;
				//TODO particle jednou za cas
			}
			break;
	}
}

void enemy::draw() {
	float temp;
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	switch (type) {
		//domy
		case enemy_house:
			glRotatef(rot,0,0,1);

			glBegin(GL_QUADS);
			//strecha
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
			
			//steny
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
		//lide
		case enemy_person:
			glColor3f(1,1,1);
			//telo
			glBegin(GL_LINE_STRIP);
			glVertex3f(-size_p/2,0,0);
			glVertex3f(0,0,size_p/2);
			glVertex3f(size_p/2,0,0);
			glVertex3f(0,0,size_p/2);
			glVertex3f(0,0,size_p);
			glVertex3f(size_p/2,0,3*size_p/4);
			glVertex3f(0,0,size_p);
			glVertex3f(-size_p/2,0,3*size_p/4);
			glVertex3f(0,0,size_p);
			glVertex3f(0,0,3*size_p/2);
			glEnd();

			//hlava
			glColor3f(1,0,0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0,0,3*size_p/2);
			glVertex3f(0,-size_p/4,size_p+3*size_p/4);
			glVertex3f(-size_p/4,0,size_p+3*size_p/4);
			glVertex3f(0,size_p/4,size_p+3*size_p/4);
			glVertex3f(size_p/4,0,size_p+3*size_p/4);
			glVertex3f(0,-size_p/4,size_p+3*size_p/4);
			glEnd();
			glColor3f(1,1,0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0,0,2*size_p);
			glVertex3f(0,-size_p/4,size_p+3*size_p/4);
			glVertex3f(size_p/4,0,size_p+3*size_p/4);
			glVertex3f(0,size_p/4,size_p+3*size_p/4);
			glVertex3f(-size_p/4,0,size_p+3*size_p/4);
			glVertex3f(0,-size_p/4,size_p+3*size_p/4);
			glEnd();
			break;
		//stromy
		case enemy_tree:
			//kmen
			glColor3f(1,0.5,0);
			glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,0,size_tr/2);
			glEnd();
			//koruna
			glColor3f(0.5,1,0.5);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0,0,size_tr/2);
			glVertex3f(0,-size_tr/2,size_tr+size_tr/4);
			glVertex3f(-size_tr/2,0,size_tr+size_tr/4);
			glVertex3f(0,size_tr/2,size_tr+size_tr/4);
			glVertex3f(size_tr/2,0,size_tr+size_tr/4);
			glVertex3f(0,-size_tr/2,size_tr+size_tr/4);
			glEnd();
			glColor3f(0.2,1,0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0,0,2*size_tr);
			glVertex3f(0,-size_tr/2,size_tr+size_tr/4);
			glVertex3f(size_tr/2,0,size_tr+size_tr/4);
			glVertex3f(0,size_tr/2,size_tr+size_tr/4);
			glVertex3f(-size_tr/2,0,size_tr+size_tr/4);
			glVertex3f(0,-size_tr/2,size_tr+size_tr/4);
			glEnd();
			break;
	}
	glPopMatrix();
}

//prijeti poskozeni a horeni
void enemy::accept_damage(float dmg, float fire) {
	hp-=dmg;
	burning+=fire;
}

#define max(a,b) (((a)>(b))?(a):(b))
//kolize nepratel se strelami
bool enemy::collides(vect missile_pos) {
	if((pos-missile_pos).length() < 0.7*max(max(size_x,size_y),size_z+roof_size)) return true;
	return false;
}

//funkce pro overeni smazatelnosti strely
bool enemy::deletable() {
	if(hp<0) return true;
	return false;
}


