
#include <GL/gl.h>
#include <math.h>

#include "imageloader.h"

#include "particles.h"

void particle_system::init() {
	particles.clear();
	tex_fire=imageloader_load("data/particle.png",1,GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D,tex_fire);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);;
	tex_smoke=imageloader_load("data/particle_smoke.png",1,GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D,tex_smoke);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);;
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);
	glDepthMask(0);
	for(list<particle>::iterator i=particles.begin();i!=particles.end();++i)
		i->draw();
	glDepthMask(1);
	glDisable(GL_BLEND);
}

void particle_system::finish() {
	particles.clear();
	imageloader_free(tex_fire);
	imageloader_free(tex_smoke);
}	

/* =========================================================== */

void particle::update(float time) {
	pos+=time*spd;
	age+=time;
	switch (type) {
		case part_fire:
			break;
		case part_spark:
			spd.z-=time*0.01;
			break;
		case part_smoke:
			spd*=powf(0.8,time);
			spd.z+=time*0.01;
			break;
	}
}

void particle::draw() {
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glColor3f(r,g,b);
	switch (type) {
		case part_fire:
			break;
		case part_spark:
			glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glColor3f(0,0,0);
			glVertex3f(-spd.x,-spd.y,-spd.z);
			glEnd();
			break;
		case part_smoke:
			break;
	}
	glPopMatrix();
}

