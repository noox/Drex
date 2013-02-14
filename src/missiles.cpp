
#include <GL/gl.h>

#include "missiles.h"
#include "frand.h"
#include "world.h"

void missile_system::init() {
	missiles.clear();
}

//pridani jedne strely
missile& missile_system::add_one() {
	missiles.push_back(missile());
	return missiles.back();
}

//update vsech strel a smazani nepotrebnych
void missile_system::update(float time, world& w) {
	list<list<missile>::iterator> todel;
	for(list<missile>::iterator i=missiles.begin();i!=missiles.end();++i) {
		i->update(time,w);
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

void missile::update(float time, world& w) {
	pos+=spd*time;
	age+=time;
	reload+=time;

	while(reload>=0) { 
		switch (type) {
			//zakladni draci utok
			case missile_dragon_fire:
				//pokud existuje moc dlouho
				if(age>3) deletable=true;
				
				//pokud zasahla cil
				if(w.es.try_to_do_damage(pos,power,10))
					deletable=true;
				
				//pridani particlu do systemu
				{particle& p=w.ps.add_one();
				p.pos=pos;
				p.spd=vect(DFRAND,DFRAND,DFRAND);
				p.type=part_fire;
				p.life=0.4;
				p.r=1;
				p.g=FRAND/2;
				p.b=0.01;}
				//TODO particle jednou za cas
				break;
			//pokrocily draci utok
			case missile_dragon_ball:
				if(age>10) deletable=true;
				break;
			default: 
				break;
		}
		reload-=0.01;
	}
}

void missile::draw() {

}



