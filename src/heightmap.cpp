
#include "imageloader.h"
#include "heightmap.h"
 
#define hm_vertex(x,y) glColor3ub(c[3*(y*size_x+x)],c[3*(y*size_x+x)+1],c[3*(y*size_x+x)+2]); glNormal3fv(normal[x+y*size_x].v); glTexCoord2f(x,y); glVertex3f(5*(x),5*(y),5*(0.1*h[y*size_x+x]));

void heightmap::init() {
	t = imageloader_load("data/terrain.png",1,GL_LUMINANCE);
	glBindTexture(GL_TEXTURE_2D,t);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void heightmap::draw() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,t);
        for(int i=0;i<size_y;++i) {
                glBegin(GL_TRIANGLE_STRIP);
                for(int j=0;j<size_x;++j) {
                        hm_vertex(i,j)
                        hm_vertex(i+1,j)
                }
                glEnd();
        }
	glDisable(GL_TEXTURE_2D);	
}
 
void heightmap::load(const char* fn,const char* fn2) {
        free();
        imageloader_load_heightmap(fn,h,size_x,size_y);
        imageloader_load_color(fn2,c,size_x,size_y);
 
        //spocita normaly
        normal.resize(size_x*size_y);
        int i,j,a,b,c,d;
        for(i=0;i<size_x;++i) {
                a=i-1;
                if(a<0) a=0;
                b=i+1;
                if(b>=size_x) b=size_x-1;
                for(j=0;j<size_y;++j) {
                        c=j-1;
                        if(c<0) c=0;
                        d=j+1;
                        if(d>=size_y) d=size_y-1;
                       
                        vect A=vect(0,(d-c),0.1*(h[i+d*size_x]-h[i+c*size_x])),
                             B=vect((b-a),0,0.1*(h[b+j*size_x]-h[a+j*size_x]));
                       
                        normal[i+j*size_x]=(B^A).normal();
                }
        }
}
 
void heightmap::free() {
        h.clear();
        c.clear();
        normal.clear();
        size_x=0;
        size_y=0;
}

void heightmap::finish() {
	imageloader_free(t);
}

