
#include "wings.h"

//zmeny tvaru pro mavani kridel
void wings_movement(vect points[][2], int &wings) {
	if(((wings>=400) && (wings<405)) || ((wings>=515) && (wings<520))) {
		points[14][0]=vect(4,12,-0.5);
		points[15][0]=vect(6.5,11,-1);
		points[16][0]=vect(8,9,-1.5);
		points[17][0]=vect(3.5,8,-0.5);
		points[18][0]=vect(5.5,8,-1);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=405) && (wings<410)) || ((wings>=520) && (wings<525))) {
		points[14][0]=vect(4,12,-0.25);
		points[15][0]=vect(6.5,11,-0.75);
		points[16][0]=vect(8,9,-1.4);
		points[17][0]=vect(3.5,8,-0.6);
		points[18][0]=vect(5.5,8,-0.75);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=410) && (wings<415)) || ((wings>=525) && (wings<530))) {
		points[14][0]=vect(4,12,0);
		points[15][0]=vect(6.5,11,-0.5);
		points[16][0]=vect(8,9,-1.25);
		points[17][0]=vect(3.5,8,-0.75);
		points[18][0]=vect(5.5,8,-0.5);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=415) && (wings<420)) || ((wings>=530) && (wings<535))) {
		points[14][0]=vect(4,12,0.5);
		points[15][0]=vect(6.5,11,-0.25);
		points[16][0]=vect(8,9,-1.1);
		points[17][0]=vect(3.5,8,0.3);
		points[18][0]=vect(5.5,8,-0.25);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=420) && (wings<425)) || ((wings>=535) && (wings<540))) {
		points[14][0]=vect(4,12,0.75);
		points[15][0]=vect(6.5,11,0);
		points[16][0]=vect(8,9,-1);
		points[17][0]=vect(3.5,8,1);
		points[18][0]=vect(5.5,8,0);
		points[19][0]=vect(8,6,-2);
		wings++;
	}
	if(((wings>=425) && (wings<430)) || ((wings>=540) && (wings<545))) {
		points[14][0]=vect(4,12,1.1);
		points[15][0]=vect(6.6,11,0.25);
		points[16][0]=vect(8.25,9,-0.6);
		points[17][0]=vect(3.5,8,1.1);
		points[18][0]=vect(5.6,8,0.25);
		points[19][0]=vect(8.4,6,-1.5);
		wings++;
	}
	if(((wings>=430) && (wings<435)) || ((wings>=545) && (wings<550))) {
		points[14][0]=vect(4,12,1.25);
		points[15][0]=vect(6.75,11,0.5);
		points[16][0]=vect(8.5,9,-0.25);
		points[17][0]=vect(3.5,8,1.25);
		points[18][0]=vect(5.75,8,0.5);
		points[19][0]=vect(8.75,6,-1);
		wings++;
	}
	if(((wings>=435) && (wings<440)) || ((wings>=550) && (wings<555))) {
		points[14][0]=vect(4,12,1.4);
		points[15][0]=vect(6.9,11,0.75);
		points[16][0]=vect(8.75,9,0.1);
		points[17][0]=vect(3.5,8,1.4);
		points[18][0]=vect(5.9,8,0.75);
		points[19][0]=vect(9.1,6,-0.5);
		wings++;
	}
	if(((wings>=440) && (wings<445)) || ((wings>=555) && (wings<560))) {
		points[14][0]=vect(4,12,1.5);
		points[15][0]=vect(7,11,1);
		points[16][0]=vect(9,9,0.5);
		points[17][0]=vect(3.5,8,1.5);
		points[18][0]=vect(6,8,1);
		points[19][0]=vect(9.5,6,0);
		wings++;
	}
	if(((wings>=445) && (wings<450)) || ((wings>=560) && (wings<565))) {
		points[14][0]=vect(4,12,1.25);
		points[15][0]=vect(7.25,11,1);
		points[16][0]=vect(9.25,9,0.75);
		points[17][0]=vect(3.6,8,1.25);
		points[18][0]=vect(6.25,8,1);
		points[19][0]=vect(9.75,6,0.5);
		wings++;
	}
	if(((wings>=450) && (wings<455)) || ((wings>=556) && (wings<570))) {
		points[14][0]=vect(4.5,12,1);
		points[15][0]=vect(7.5,11,1);
		points[16][0]=vect(9.5,9,1);
		points[17][0]=vect(3.75,8,1);
		points[18][0]=vect(6.5,8,1);
		points[19][0]=vect(10.25,6,1);
		wings++;
	}
	if(((wings>=455) && (wings<460)) || ((wings>=570) && (wings<575))) {
		points[14][0]=vect(4.75,12,0.75);
		points[15][0]=vect(7.75,11,1);
		points[16][0]=vect(9.75,9,1.25);
		points[17][0]=vect(3.9,8,0.75);
		points[18][0]=vect(6.75,8,1);
		points[19][0]=vect(10.6,6,1.5);
		wings++;
	}
	if(((wings>=460) && (wings<465)) || ((wings>=575) && (wings<580))) {
		points[14][0]=vect(4.9,12,0.6);
		points[15][0]=vect(7.9,11,1);
		points[16][0]=vect(9.9,9,1.4);
		points[17][0]=vect(3.95,8,0.6);
		points[18][0]=vect(6.9,8,1);
		points[19][0]=vect(10.8,6,2);
		wings++;
	}
	if(((wings>=465) && (wings<470)) || ((wings>=580) && (wings<585))) {
		points[14][0]=vect(5,12,0.5);
		points[15][0]=vect(8,11,1);
		points[16][0]=vect(10,9,1.5);
		points[17][0]=vect(4,8,0.5);
		points[18][0]=vect(7,8,1);
		points[19][0]=vect(11,6,2.5);
		wings++;
	}
	if(((wings>=470) && (wings<475)) || ((wings>=585) && (wings<590))) {
		points[14][0]=vect(5,12,0.45);
		points[15][0]=vect(8,11,0.9);
		points[16][0]=vect(10,9,1.3);
		points[17][0]=vect(4,8,0.45);
		points[18][0]=vect(7,8,0.9);
		points[19][0]=vect(11,6,2.2);
		wings++;
	}

	if(((wings>=475) && (wings<480)) || ((wings>=590) && (wings<595))) {
		points[14][0]=vect(5,12,0.4);
		points[15][0]=vect(8,11,0.75);
		points[16][0]=vect(10,9,1.1);
		points[17][0]=vect(4,8,0.4);
		points[18][0]=vect(7,8,0.75);
		points[19][0]=vect(11,6,1.9);
		wings++;
	}
	if(((wings>=480) && (wings<485)) || ((wings>=595) && (wings<600))) {
		points[14][0]=vect(5,12,0.3);
		points[15][0]=vect(8,11,0.6);
		points[16][0]=vect(10,9,1.4);
		points[17][0]=vect(4,8,0.3);
		points[18][0]=vect(7,8,0.6);
		points[19][0]=vect(11,6,1.6);
		wings++;
	}
	if(((wings>=485) && (wings<490)) || ((wings>=600) && (wings<605))) {
		points[14][0]=vect(5,12,0.25);
		points[15][0]=vect(8,11,0.5);
		points[16][0]=vect(10,9,0.75);
		points[17][0]=vect(4,8,0.25);
		points[18][0]=vect(7,8,0.5);
		points[19][0]=vect(11,6,1.25);
		wings++;
	}
	if(((wings>=490) && (wings<495)) || ((wings>=605) && (wings<610))) {
		points[14][0]=vect(5,12,0.15);
		points[15][0]=vect(8,11,0.4);
		points[16][0]=vect(10,9,0.6);
		points[17][0]=vect(4,8,0.15);
		points[18][0]=vect(7,8,0.4);
		points[19][0]=vect(11,6,0.9);
		wings++;
	}
	if(((wings>=495) && (wings<500)) || ((wings>=610) && (wings<615))) {
		points[14][0]=vect(5,12,0.1);
		points[15][0]=vect(8,11,0.25);
		points[16][0]=vect(10,9,0.4);
		points[17][0]=vect(4,8,0.1);
		points[18][0]=vect(7,8,0.25);
		points[19][0]=vect(11,6,0.6);
		wings++;
	}
	if(((wings>=500) && (wings<505)) || ((wings>=615) && (wings<620))) {
		points[14][0]=vect(5,12,0.05);
		points[15][0]=vect(8,11,0.15);
		points[16][0]=vect(10,9,0.2);
		points[17][0]=vect(4,8,0.05);
		points[18][0]=vect(7,8,0.15);
		points[19][0]=vect(11,6,0.3);
		if(wings>=619) wings=0;
		wings++;
	}
}

