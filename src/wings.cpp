
#include "wings.h"

//zmeny tvaru pro mavani kridel
void wings_movement(vect points[][2], int &wings) {
	int x=400,y=520,jump=4;
	if(((wings>=x) && (wings<x+jump)) || ((wings>=y) && (wings<y+jump))) {
		points[14][0]=vect(4,12,-0.5);
		points[15][0]=vect(6.5,11,-1);
		points[16][0]=vect(8,9,-1.5);
		points[17][0]=vect(3.5,8,-0.5);
		points[18][0]=vect(5.5,8,-1);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=x+jump) && (wings<x+2*jump)) || ((wings>=y+jump) && (wings<y+2*jump))) {
		points[14][0]=vect(4,12,-0.25);
		points[15][0]=vect(6.5,11,-0.75);
		points[16][0]=vect(8,9,-1.4);
		points[17][0]=vect(3.5,8,-0.6);
		points[18][0]=vect(5.5,8,-0.75);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=x+2*jump) && (wings<x+3*jump)) || ((wings>=y+2*jump) && (wings<y+3*jump))) {
		points[14][0]=vect(4,12,0);
		points[15][0]=vect(6.5,11,-0.5);
		points[16][0]=vect(8,9,-1.25);
		points[17][0]=vect(3.5,8,-0.75);
		points[18][0]=vect(5.5,8,-0.5);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=x+3*jump) && (wings<x+4*jump)) || ((wings>=y+3*jump) && (wings<y+4*jump))) {
		points[14][0]=vect(4,12,0.5);
		points[15][0]=vect(6.5,11,-0.25);
		points[16][0]=vect(8,9,-1.1);
		points[17][0]=vect(3.5,8,0.3);
		points[18][0]=vect(5.5,8,-0.25);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=x+4*jump) && (wings<x+5*jump)) || ((wings>=y+4*jump) && (wings<y+5*jump))) {
		points[14][0]=vect(4,12,0.75);
		points[15][0]=vect(6.5,11,0);
		points[16][0]=vect(8,9,-1);
		points[17][0]=vect(3.5,8,1);
		points[18][0]=vect(5.5,8,0);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=x+5*jump) && (wings<x+6*jump)) || ((wings>=y+5*jump) && (wings<y+6*jump))) {
		points[14][0]=vect(4,12,1.1);
		points[15][0]=vect(6.6,11,0.25);
		points[16][0]=vect(8.25,9,-0.6);
		points[17][0]=vect(3.5,8,1.1);
		points[18][0]=vect(5.6,8,0.25);
		points[19][0]=vect(8.4,6,-1.5);
		wings++;
	}
	if(((wings>=x+6*jump) && (wings<x+7*jump)) || ((wings>=y+6*jump) && (wings<y+7*jump))) {
		points[14][0]=vect(4,12,1.25);
		points[15][0]=vect(6.75,11,0.5);
		points[16][0]=vect(8.5,9,-0.25);
		points[17][0]=vect(3.5,8,1.25);
		points[18][0]=vect(5.75,8,0.5);
		points[19][0]=vect(8.75,6,-1);
		wings++;
	}
	if(((wings>=x+7*jump) && (wings<x+8*jump)) || ((wings>=y+7*jump) && (wings<y+8*jump))) {
		points[14][0]=vect(4,12,1.4);
		points[15][0]=vect(6.9,11,0.75);
		points[16][0]=vect(8.75,9,0.1);
		points[17][0]=vect(3.5,8,1.4);
		points[18][0]=vect(5.9,8,0.75);
		points[19][0]=vect(9.1,6,-0.5);
		wings++;
	}
	if(((wings>=x+8*jump) && (wings<x+9*jump)) || ((wings>=y+8*jump) && (wings<y+9*jump))) {
		points[14][0]=vect(4,12,1.5);
		points[15][0]=vect(7,11,1);
		points[16][0]=vect(9,9,0.5);
		points[17][0]=vect(3.5,8,1.5);
		points[18][0]=vect(6,8,1);
		points[19][0]=vect(9.5,6,0);
		wings++;
	}
	if(((wings>=x+9*jump) && (wings<x+10*jump)) || ((wings>=y+9*jump) && (wings<y+10*jump))) {
		points[14][0]=vect(4,12,1.25);
		points[15][0]=vect(7.25,11,1);
		points[16][0]=vect(9.25,9,0.75);
		points[17][0]=vect(3.6,8,1.25);
		points[18][0]=vect(6.25,8,1);
		points[19][0]=vect(9.75,6,0.5);
		wings++;
	}
	if(((wings>=x+10*jump) && (wings<x+11*jump)) || ((wings>=y+10*jump) && (wings<y+11*jump))) {
		points[14][0]=vect(4.5,12,1);
		points[15][0]=vect(7.5,11,1);
		points[16][0]=vect(9.5,9,1);
		points[17][0]=vect(3.75,8,1);
		points[18][0]=vect(6.5,8,1);
		points[19][0]=vect(10.25,6,1);
		wings++;
	}
	if(((wings>=x+11*jump) && (wings<x+12*jump)) || ((wings>=y+11*jump) && (wings<y+12*jump))) {
		points[14][0]=vect(4.75,12,0.75);
		points[15][0]=vect(7.75,11,1);
		points[16][0]=vect(9.75,9,1.25);
		points[17][0]=vect(3.9,8,0.75);
		points[18][0]=vect(6.75,8,1);
		points[19][0]=vect(10.6,6,1.5);
		wings++;
	}
	if(((wings>=x+12*jump) && (wings<x+13*jump)) || ((wings>=y+12*jump) && (wings<y+13*jump))) {
		points[14][0]=vect(4.9,12,0.6);
		points[15][0]=vect(7.9,11,1);
		points[16][0]=vect(9.9,9,1.4);
		points[17][0]=vect(3.95,8,0.6);
		points[18][0]=vect(6.9,8,1);
		points[19][0]=vect(10.8,6,2);
		wings++;
	}
	if(((wings>=x+13*jump) && (wings<x+14*jump)) || ((wings>=y+13*jump) && (wings<y+14*jump))) {
		points[14][0]=vect(5,12,0.5);
		points[15][0]=vect(8,11,1);
		points[16][0]=vect(10,9,1.5);
		points[17][0]=vect(4,8,0.5);
		points[18][0]=vect(7,8,1);
		points[19][0]=vect(11,6,2.5);
		wings++;
	}
	if(((wings>=x+14*jump) && (wings<x+15*jump)) || ((wings>=y+14*jump) && (wings<y+15*jump))) {
		points[14][0]=vect(5,12,0.45);
		points[15][0]=vect(8,11,0.9);
		points[16][0]=vect(10,9,1.3);
		points[17][0]=vect(4,8,0.45);
		points[18][0]=vect(7,8,0.9);
		points[19][0]=vect(11,6,2.2);
		wings++;
	}

	if(((wings>=x+15*jump) && (wings<x+16*jump)) || ((wings>=y+15*jump) && (wings<y+16*jump))) {
		points[14][0]=vect(5,12,0.4);
		points[15][0]=vect(8,11,0.75);
		points[16][0]=vect(10,9,1.1);
		points[17][0]=vect(4,8,0.4);
		points[18][0]=vect(7,8,0.75);
		points[19][0]=vect(11,6,1.9);
		wings++;
	}
	if(((wings>=x+16*jump) && (wings<x+17*jump)) || ((wings>=y+16*jump) && (wings<y+17*jump))) {
		points[14][0]=vect(5,12,0.3);
		points[15][0]=vect(8,11,0.6);
		points[16][0]=vect(10,9,1.4);
		points[17][0]=vect(4,8,0.3);
		points[18][0]=vect(7,8,0.6);
		points[19][0]=vect(11,6,1.6);
		wings++;
	}
	if(((wings>=x+17*jump) && (wings<x+18*jump)) || ((wings>=y+17*jump) && (wings<y+18*jump))) {
		points[14][0]=vect(5,12,0.25);
		points[15][0]=vect(8,11,0.5);
		points[16][0]=vect(10,9,0.75);
		points[17][0]=vect(4,8,0.25);
		points[18][0]=vect(7,8,0.5);
		points[19][0]=vect(11,6,1.25);
		wings++;
	}
	if(((wings>=x+18*jump) && (wings<x+19*jump)) || ((wings>=y+18*jump) && (wings<y+19*jump))) {
		points[14][0]=vect(5,12,0.15);
		points[15][0]=vect(8,11,0.4);
		points[16][0]=vect(10,9,0.6);
		points[17][0]=vect(4,8,0.15);
		points[18][0]=vect(7,8,0.4);
		points[19][0]=vect(11,6,0.9);
		wings++;
	}
	if(((wings>=x+19*jump) && (wings<x+20*jump)) || ((wings>=y+19*jump) && (wings<y+20*jump))) {
		points[14][0]=vect(5,12,0.1);
		points[15][0]=vect(8,11,0.25);
		points[16][0]=vect(10,9,0.4);
		points[17][0]=vect(4,8,0.1);
		points[18][0]=vect(7,8,0.25);
		points[19][0]=vect(11,6,0.6);
		wings++;
	}
	if(((wings>=x+20*jump) && (wings<x+21*jump)) || ((wings>=y+20*jump) && (wings<y+21*jump))) {
		points[14][0]=vect(5,12,0.05);
		points[15][0]=vect(8,11,0.15);
		points[16][0]=vect(10,9,0.2);
		points[17][0]=vect(4,8,0.05);
		points[18][0]=vect(7,8,0.15);
		points[19][0]=vect(11,6,0.3);
		if(wings>=(y+(21*jump)-2)) wings=0;
		wings++;
	}
}

