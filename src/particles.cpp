
#include <GL/gl.h>
#include <math.h>

#include "world.h"
#include "imageloader.h"

#include "particles.h"

void particle_system::init() {
	particles.clear();
	tex_fire = imageloader_load ("data/particle.png", 1, GL_LUMINANCE);
	glBindTexture (GL_TEXTURE_2D, tex_fire);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);;
	tex_smoke = imageloader_load ("data/particle_smoke.png", 1, GL_LUMINANCE);
	glBindTexture (GL_TEXTURE_2D, tex_smoke);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);;
}

//pridani jednoho particlu do systemu
particle& particle_system::add_one() {
	particles.push_back (particle() );
	return particles.back();
}

//update vsech particlu a smazani nepotrebnych
void particle_system::update (float time) {
	list<list<particle>::iterator> todel;
	for (list<particle>::iterator i = particles.begin();i != particles.end();++i) {
		i->update (time);
		if (i->age > i->life) todel.push_back (i);
	}
	while (!todel.empty() ) {
		particles.erase (todel.front() );
		todel.pop_front();
	}
}

void particle_system::draw (world &w) {
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

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	glDepthMask (0);
	for (list<particle>::iterator i = particles.begin();i != particles.end();++i) {
		glPushMatrix();
		glTranslatef (i->pos.x, i->pos.y, i->pos.z);
		glColor4f (i->r, i->g, i->b, 1 - (i->age / i->life) );
		switch (i->type) {
		case part_fire:
			glBindTexture (GL_TEXTURE_2D, tex_fire);
			glEnable (GL_TEXTURE_2D);
			glMultMatrixf (part_face);
			glBegin (GL_QUADS);
			glTexCoord2f (0, 0);
			glVertex3f (-0.2, -0.2, 0);
			glTexCoord2f (1, 0);
			glVertex3f (0.2, -0.2, 0);
			glTexCoord2f (1, 1);
			glVertex3f (0.2, 0.2, 0);
			glTexCoord2f (0, 1);
			glVertex3f (-0.2, 0.2, 0);
			glEnd();
			glDisable (GL_TEXTURE_2D);
			break;
		case part_spark:
			glBegin (GL_LINES);
			glVertex3f (0, 0, 0);
			glColor4f (0, 0, 0, 0);
			glVertex3f (- (i->spd.x), - (i->spd.y), - (i->spd.z) );
			glEnd();
			break;
		case part_smoke:
			glBindTexture (GL_TEXTURE_2D, tex_smoke);
			glEnable (GL_TEXTURE_2D);
			glMultMatrixf (part_face);
			glBegin (GL_QUADS);
			glTexCoord2f (0, 0);
			glVertex3f (-0.2, -0.2, 0);
			glTexCoord2f (1, 0);
			glVertex3f (0.2, -0.2, 0);
			glTexCoord2f (1, 1);
			glVertex3f (0.2, 0.2, 0);
			glTexCoord2f (0, 1);
			glVertex3f (-0.2, 0.2, 0);
			glEnd();
			glDisable (GL_TEXTURE_2D);
			break;
		case part_rain:
			glBegin (GL_LINES);
			glVertex3f (0, 0, -2);
			glColor4f (0, 0, 0, 0);
			glVertex3f (0, 0, 0);
			glEnd();
			break;
		case part_snow:
			glBindTexture (GL_TEXTURE_2D, tex_smoke);
			glEnable (GL_TEXTURE_2D);
			glMultMatrixf (part_face);
			glBegin (GL_QUADS);
			glTexCoord2f (0, 0);
			glVertex3f (-0.2, -0.2, 0);
			glTexCoord2f (1, 0);
			glVertex3f (0.2, -0.2, 0);
			glTexCoord2f (1, 1);
			glVertex3f (0.2, 0.2, 0);
			glTexCoord2f (0, 1);
			glVertex3f (-0.2, 0.2, 0);
			glEnd();
			glDisable (GL_TEXTURE_2D);
			break;
		}
		glPopMatrix();
	}
	glDepthMask (1);
	glDisable (GL_BLEND);
}

void particle_system::finish() {
	particles.clear();
	imageloader_free (tex_fire);
	imageloader_free (tex_smoke);
}

/* =========================================================== */

void particle::update (float time) {
	pos += time * spd;
	age += time;
	switch (type) {
	case part_fire:
		break;
	case part_spark:
		spd.z -= time * 0.01;
		break;
	case part_smoke:
		spd *= powf (0.8, time);
		spd.z += time;
		break;
	case part_rain:
		spd.z -= time;
		break;
	}
}

