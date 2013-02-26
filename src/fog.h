#ifndef _FOG_H_
#define _FOG_H_

class fog {
	float r, g, b, minfog, maxfog;
public:
	void set_color (float R, float G, float B) {
		r = R;
		g = G;
		b = B;
	};
	void set_distance (int Minfog, int Maxfog) {
		minfog = Minfog;
		maxfog = Maxfog;
	};
	void turn_on();
	void turn_off();
};

#endif

