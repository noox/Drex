
#include "game.h"

#ifndef _SOUND_H_
#define _SOUND_H_

#include <AL/al.h>
#include <AL/alc.h>	
#include <vector>
#include <string>

#include "vector.h"

class world;

enum sound_type {
	fireball1,
	fireball2,
	arrow,
	wing,
	burn,
	wind,
	rain
};

class sound
{
	vector<ALuint> source, buffer;
	ALCdevice *device;
	ALCcontext *context;	
	unsigned char* buf;

	vector<string> files;
	int files_count;

	char type[4];
	unsigned int size, chunk_size;
	short format_type, channels;
	unsigned int sample_rate, avg_bytes_per_sec;
	short bytes_per_sample, bits_per_sample;
	unsigned int data_size;
public:
	int error_message(string msg);
	int init();
	void stop_game_sound();
	void start_game_sound();
	int play_fireball1(dragon& dr, missile& m);
	int play_fireball2(dragon& dr, missile& m);
	int play_arrow(dragon& dr, missile& m);
	int play_wing(dragon& dr);
	int play_burn(dragon& dr, vect p);
	int stop_burn();
	int play_rain(dragon& dr);
	int play_wind(dragon& dr);
	void finish();
};

#endif

