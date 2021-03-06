
#include <GL/gl.h>
#include <math.h>

#include "particles.h"
#include "world.h"
#include "imageloader.h"

void particle_system::init()
{
	particles.clear();

	//priprava textur
	tex_fire = imageloader_load("data/particle_fire.png", 1, GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D, tex_fire);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	tex_burning = imageloader_load("data/particle_burning.png", 1,
		GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D, tex_burning);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	tex_smoke = imageloader_load("data/particle_smoke.png", 1,
		GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D, tex_smoke);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//pridani jednoho particlu do systemu
particle& particle_system::add_one()
{
	particles.push_back(particle());
	return particles.back();
}

//update vsech particlu a smazani nepotrebnych
void particle_system::update(float time)
{
	list<list<particle>::iterator> todel;
	for (list<particle>::iterator i = particles.begin();
	        i != particles.end();++i) {

		i->update(time);
		if (i->age > i->life) todel.push_back(i);
	}
	while (!todel.empty()) {
		particles.erase(todel.front());
		todel.pop_front();
	}
}

void particle_system::draw(world &w)
{
	//priprava matice pro billboarding
	float part_face[16];
	for (int i = 0;i < 16;++i) part_face[i] = 0;
	vect temp = w.cam.ori.vecx();
	part_face[0] = temp.x;
	part_face[1] = temp.y;
	part_face[2] = temp.z;
	part_face[3] = 0;
	temp = w.cam.ori.vecy();
	part_face[4] = temp.x;
	part_face[5] = temp.y;
	part_face[6] = temp.z;
	part_face[7] = 0;
	temp = w.cam.ori.vecz();
	part_face[8] = temp.x;
	part_face[9] = temp.y;
	part_face[10] = temp.z;
	part_face[11] = 0;
	part_face[12] = 0;
	part_face[13] = 0;
	part_face[14] = 0;
	part_face[15] = 1;
	
	//priprava matice pro billboarding particlu horeni
	float part_face2[16];
	for (int i = 0;i < 16;++i) part_face2[i] = 0;
	temp = (vect(0, 0, 1)^w.cam.ori.vecz()).normal();
	part_face2[0] = temp.x;
	part_face2[1] = temp.y;
	part_face2[2] = temp.z;
	part_face2[3] = 0;
	temp = vect(0, 0, 1);
	part_face2[4] = temp.x;
	part_face2[5] = temp.y;
	part_face2[6] = temp.z;
	part_face2[7] = 0;
	temp = (vect(0, 0, 1)^vect(1, 0, 0)).normal();
	part_face2[8] = temp.x;
	part_face2[9] = temp.y;
	part_face2[10] = temp.z;
	part_face2[11] = 0;
	part_face2[12] = 0;
	part_face2[13] = 0;
	part_face2[14] = 0;
	part_face2[15] = 1;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(0);
	for (list<particle>::iterator i = particles.begin();
	        i != particles.end();++i) {

		glPushMatrix();
		glTranslatef(i->pos.x, i->pos.y, i->pos.z);
		glColor4f(i->r, i->g, i->b, 1 - (i->age / i->life));

		switch (i->type) {
		
		//pokrocily utok draka
		case part_fireball:
			glScalef(4, 4, 4);

		//zakladni strelba draka
		case part_fire:
			glBindTexture(GL_TEXTURE_2D, tex_burning);
			glEnable(GL_TEXTURE_2D);
			glMultMatrixf(part_face);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.2, -0.2, 0);
			glTexCoord2f(1, 0);
			glVertex3f(0.2, -0.2, 0);
			glTexCoord2f(1, 1);
			glVertex3f(0.2, 0.2, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-0.2, 0.2, 0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			break;

		//horeni keru	
		case part_small_burning:
			glScalef(1, 1, 0.3);

		//horeni stromu a domu
		case part_burning:
			glBindTexture(GL_TEXTURE_2D, tex_burning);
			glEnable(GL_TEXTURE_2D);
			glMultMatrixf(part_face2);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-1, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(1, 0, 0);
			glTexCoord2f(1, 1);
			glVertex3f(1, 10, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-1, 10, 0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			break;

		//pro vybuchy, "cara"
		case part_spark:
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glColor4f(0, 0, 0, 0);
			glVertex3f(-(i->spd.x), -(i->spd.y), -(i->spd.z));
			glEnd();
			break;

		//kour a snih
		case part_smoke:
		case part_snow:
			glBindTexture(GL_TEXTURE_2D, tex_smoke);
			glEnable(GL_TEXTURE_2D);
			glMultMatrixf(part_face);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-0.2, -0.2, 0);
			glTexCoord2f(1, 0);
			glVertex3f(0.2, -0.2, 0);
			glTexCoord2f(1, 1);
			glVertex3f(0.2, 0.2, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-0.2, 0.2, 0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			break;

		//dest
		case part_rain:
			glBegin(GL_LINES);
			glVertex3f(0, 0, -2);
			glColor4f(0, 0, 0, 0);
			glVertex3f(0, 0, 0);
			glEnd();
			break;
		}
		glPopMatrix();
	}
	glDepthMask(1);
	glDisable(GL_BLEND);
}

void particle_system::finish()
{
	particles.clear();
	imageloader_free(tex_fire);
	imageloader_free(tex_burning);
	imageloader_free(tex_smoke);
}

/* =========================================================== */

void particle::update(float time)
{
	pos += time * spd;
	age += time;
	switch (type) {
	case part_fire:
		break;
	case part_spark:
		spd.z -= time * 0.01;
		break;
	case part_smoke:
		spd *= powf(0.8, time);
		spd.z += time;
		break;
	case part_rain:
		spd.z -= time;
		break;
	}
}

