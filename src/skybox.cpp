#include <GL/gl.h>
 
#include "vector.h"
#include "skybox.h"
 
void skybox::draw(vect pos) {
        glDisable(GL_DEPTH_TEST);
        glDepthMask(false);
       
        glPushMatrix();
        glTranslatef(pos.x,pos.y,pos.z);
 
        float bottom_color[]={0.7,0.8,0.9};
        float top_color[]={0.1,0.4,1};
 
        glBegin(GL_QUADS);
        glColor3fv(bottom_color);
        glVertex3f(-1,-1,-1);
        glVertex3f(-1,1,-1);
        glVertex3f(1,1,-1);  
        glVertex3f(1,-1,-1);
 
        glColor3fv(top_color);
        glVertex3f(1,-1,1);
        glVertex3f(1,1,1);
        glVertex3f(-1,1,1);
        glVertex3f(-1,-1,1);
 
        glColor3fv(bottom_color);
        glVertex3f(1,-1,-1);
        glVertex3f(1,1,-1);
        glColor3fv(top_color);
        glVertex3f(1,1,1);
        glVertex3f(1,-1,1);
 
        glColor3fv(top_color);
        glVertex3f(-1,-1,1);
        glVertex3f(-1,1,1);
        glColor3fv(bottom_color);
        glVertex3f(-1,1,-1);
        glVertex3f(-1,-1,-1);
 
        glColor3fv(top_color);
        glVertex3f(-1,1,1);
        glVertex3f(1,1,1);
        glColor3fv(bottom_color);
        glVertex3f(1,1,-1);
        glVertex3f(-1,1,-1);
 
        glColor3fv(bottom_color);
        glVertex3f(-1,-1,-1);
        glVertex3f(1,-1,-1);
        glColor3fv(top_color);
        glVertex3f(1,-1,1);
        glVertex3f(-1,-1,1);
        glEnd();
 
        glPopMatrix();
 
        glDepthMask(true);
        glEnable(GL_DEPTH_TEST);
}

