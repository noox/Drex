
#include <iostream>
#include <string>

using namespace std;

#include "sound.h"

int sound::error_message(string msg)
{
	//cout << msg << endl;
	return 0;
}

int sound::init()
{
	files.push_back("fireball1");
	files.push_back("fireball2");
	files.push_back("arrow");
	files.push_back("wing");
	files.push_back("burn");
	files.push_back("wind");
	files.push_back("rain");

	files_count = files.size();

	buffer.resize(files_count);
	source.resize(files_count);

	size_t tmp;
	string t;

	//inicializace OpenAL 
	device = alcOpenDevice(NULL);
	if (!device) return error_message("no sound device");
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if (!context) return error_message("no sound context");

	for (int i = 0;i < files_count;++i) {
		//nacte vsechny potrebne wav soubory
		t = "data/" + files[i] + ".wav";
		//cout << endl << t << endl;
		FILE *f = fopen(t.c_str(), "rb"); 
		if (!f) return error_message("failed to open file");

		//kontrola wave souboru
		tmp = fread(type, sizeof(char), 4, f);
		if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' 
			|| type[3]!='F') return error_message ("no RIFF");

		tmp = fread(&size, sizeof(unsigned int), 1, f);

		tmp = fread(type, sizeof(char), 4, f);
		if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' 
			|| type[3]!='E') return error_message("not WAVE");

		tmp = fread(type, sizeof(char), 4, f);
		if (type[0] != 'f' || type[1] != 'm' || type[2] != 't'
			|| type[3]!=' ') return error_message("not fmt");

		tmp = fread(&chunk_size, sizeof(unsigned int), 1, f);
		tmp = fread(&format_type, sizeof(short), 1, f);
		tmp = fread(&channels, sizeof(short), 1, f);
		tmp = fread(&sample_rate, sizeof(unsigned int), 1, f);
		tmp = fread(&avg_bytes_per_sec, sizeof(unsigned int), 1, f);
		tmp = fread(&bytes_per_sample, sizeof(short), 1, f);
		tmp = fread(&bits_per_sample, sizeof(short), 1, f);

		//nacteni zbytku souboru az do "data"
		tmp = fread(type, sizeof(char), 1, f);
		while (type[0]!='d') 
			tmp = fread(type, sizeof(char), 1, f);
		tmp = fread(type, sizeof(char), 3, f);
		
		if (type[0]!='a' || type[1]!='t' || type[2]!='a')
			return error_message("missing data");

		tmp = fread(&data_size, sizeof(unsigned int), 1, f);

		/*
		//zobrazeni informaci o souboru
		cout << "chunk size: " << chunk_size << endl; //
		cout << "format type: " << format_type << endl; //
		cout << "channels: " << channels << endl;
		cout << "sample rate: " << sample_rate << endl;
		cout << "average bytes per second: " << avg_bytes_per_sec 
			<< endl; //
		cout << "bytes per sample: " << bytes_per_sample << endl; //
		cout << "bits per sample: " << bits_per_sample << endl;
		cout << "data size: " << data_size << endl;
		*/
		 
		buf = new unsigned char[data_size];
		tmp = fread(buf, sizeof(char), data_size, f);
		
		fclose(f);

		ALuint frequency = sample_rate;
		ALenum format = 0;

		alGenBuffers(1, &(buffer[i]));
		if (alGetError() != AL_NO_ERROR) 
			return error_message("error GenSource");

		//zjisteni formatu wave
		if (bits_per_sample == 8) {
			if (channels == 1) format = AL_FORMAT_MONO8;
			else if (channels == 2) format = AL_FORMAT_STEREO8;
		} else if (bits_per_sample == 16) {
			if (channels == 1) format = AL_FORMAT_MONO16;
			else if (channels == 2) format = AL_FORMAT_STEREO16;
		}
		if (!format) return error_message("wrong bit/sample");

		alBufferData(buffer[i], format, buf, data_size, frequency);
		if (alGetError() != AL_NO_ERROR) 
			return error_message("error loading ALBuffer");

	}
		delete[] buf;
		return 0;
}

//stop zvuku pro menu
void sound::stop_game_sound()
{
	for (int i = 0;i < files_count;++i) 
		alSourceStop(source[i]);
}

int sound::play_fireball1(dragon& dr, missile& m)
{
	//hodnoty pro posluchace a zdroje
	ALfloat source_pos[] = { m.pos.x, m.pos.y, m.pos.z };
	ALfloat source_vel[] = { m.spd.x, m.spd.y, m.spd.z };
	ALfloat listener_pos[] = { dr.pos.x, dr.pos.y, dr.pos.z };
	ALfloat listener_vel[] = { dr.spd.x, dr.spd.y, dr.spd.z };
	ALfloat listener_ori[] = { 0, 0, -1, 0, 1, 0 };

	//nastavi vlastnosti posluchace
	alListenerfv(AL_POSITION, listener_pos);
	alListenerfv(AL_VELOCITY, listener_vel);
	alListenerfv(AL_ORIENTATION, listener_ori);
	
	alGenSources(1, &(source[fireball1]));

	//nastavi vlastnosti zdroje zvuku
	alSourcei(source[fireball1], AL_BUFFER, buffer[fireball1]);
	alSourcef(source[fireball1], AL_PITCH, 0.8); 
	alSourcef(source[fireball1], AL_GAIN, 0.8);
	alSourcefv(source[fireball1], AL_POSITION, source_pos);
	alSourcefv(source[fireball1], AL_VELOCITY, source_vel);
	alSourcei(source[fireball1], AL_LOOPING, AL_FALSE);

	//prehraje zvuk
	alSourcePlay(source[fireball1]);
	
	if (alGetError() != AL_NO_ERROR)
		return error_message("error playing fireball1 sound"); 
}

int sound::play_fireball2(dragon& dr, missile& m)
{	
	//hodnoty pro posluchace a zdroje
	ALfloat source_pos[] = { m.pos.x, m.pos.y, m.pos.z };
	ALfloat source_vel[] = { m.spd.x, m.spd.y, m.spd.z };
	ALfloat listener_pos[] = { dr.pos.x, dr.pos.y, dr.pos.z };
	ALfloat listener_vel[] = { dr.spd.x, dr.spd.y, dr.spd.z };
	ALfloat listener_ori[] = { 0, 0, -1, 0, 1, 0 };

	//nastavi vlastnosti posluchace
	alListenerfv(AL_POSITION, listener_pos);
	alListenerfv(AL_VELOCITY, listener_vel);
	alListenerfv(AL_ORIENTATION, listener_ori);

	alGenSources(1, &(source[fireball2]));

	//nastavi vlastnosti zdroje zvuku
	alSourcei(source[fireball2], AL_BUFFER, buffer[fireball2]);
	alSourcef(source[fireball2], AL_PITCH, 1); 
	alSourcef(source[fireball2], AL_GAIN, 1);
	alSourcefv(source[fireball2], AL_POSITION, source_pos);
	alSourcefv(source[fireball2], AL_VELOCITY, source_vel);
	alSourcei(source[fireball2], AL_LOOPING, AL_FALSE);

	//prehraje zvuk
	alSourcePlay(source[fireball2]);

	if (alGetError() != AL_NO_ERROR) 
		return error_message("error playing fireball2 sound"); 
}

int sound::play_arrow(dragon& dr, missile& m)
{
	//hodnoty pro posluchace a zdroje
	ALfloat source_pos[] = { m.pos.x, m.pos.y, m.pos.z };
	ALfloat source_vel[] = { m.spd.x, m.spd.y, m.spd.z };
	ALfloat listener_pos[] = { dr.pos.x, dr.pos.y, dr.pos.z };
	ALfloat listener_vel[] = { dr.spd.x, dr.spd.y, dr.spd.z };
	ALfloat listener_ori[] = { 0, 0, -1, 0, 1, 0 };

	//nastavi vlastnosti posluchace
	alListenerfv(AL_POSITION, listener_pos);
	alListenerfv(AL_VELOCITY, listener_vel);
	alListenerfv(AL_ORIENTATION, listener_ori);
	
	alGenSources(1, &(source[arrow]));

	//nastavi vlastnosti zdroje zvuku
	alSourcei(source[arrow], AL_BUFFER, buffer[arrow]);
	alSourcef(source[arrow], AL_PITCH, 1); 
	alSourcef(source[arrow], AL_GAIN, 1);
	alSourcefv(source[arrow], AL_POSITION, source_pos);
	alSourcefv(source[arrow], AL_VELOCITY, source_vel);
	alSourcei(source[arrow], AL_LOOPING, AL_FALSE);

	//prehraje zvuk
	alSourcePlay(source[arrow]);
	
	if (alGetError() != AL_NO_ERROR)
		return error_message("error playing arrow sound"); 
}

int sound::play_wing(dragon& dr)
{
	//hodnoty pro posluchace a zdroje
	ALfloat source_pos[] = { dr.pos.x, dr.pos.y, dr.pos.z };
	ALfloat source_vel[] = { dr.spd.x, dr.spd.y, dr.spd.z };
	ALfloat listener_pos[] = { dr.pos.x, dr.pos.y, dr.pos.z };
	ALfloat listener_vel[] = { dr.spd.x, dr.spd.y, dr.spd.z };
	ALfloat listener_ori[] = { 0, 0, -1, 0, 1, 0 };

	//nastavi vlastnosti posluchace
	alListenerfv(AL_POSITION, listener_pos);
	alListenerfv(AL_VELOCITY, listener_vel);
	alListenerfv(AL_ORIENTATION, listener_ori);
	
	alGenSources(1, &(source[wing]));

	//nastavi vlastnosti zdroje zvuku
	alSourcei(source[wing], AL_BUFFER, buffer[wing]);
	alSourcef(source[wing], AL_PITCH, 0.4); 
	alSourcef(source[wing], AL_GAIN, 0.1);
	alSourcefv(source[wing], AL_POSITION, source_pos);
	alSourcefv(source[wing], AL_VELOCITY, source_vel);
	alSourcei(source[wing], AL_LOOPING, AL_FALSE);

	//prehraje zvuk
	alSourcePlay(source[wing]);
	
	if (alGetError() != AL_NO_ERROR)
		return error_message("error playing wing sound"); 
}

int sound::play_burn(dragon& dr, vect p)
{
	//hodnoty pro posluchace a zdroje
	ALfloat source_pos[] = { p.x, p.y, p.z };
	ALfloat source_vel[] = { 0, 0, 0 };
	ALfloat listener_pos[] = { dr.pos.x, dr.pos.y, dr.pos.z };
	ALfloat listener_vel[] = { dr.spd.x, dr.spd.y, dr.spd.z };
	ALfloat listener_ori[] = { 0, 0, -1, 0, 1, 0 };

	//nastavi vlastnosti posluchace
	alListenerfv(AL_POSITION, listener_pos);
	alListenerfv(AL_VELOCITY, listener_vel);
	alListenerfv(AL_ORIENTATION, listener_ori);
	
	alGenSources(1, &(source[burn]));

	//nastavi vlastnosti zdroje zvuku
	alSourcei(source[burn], AL_BUFFER, buffer[burn]);
	alSourcef(source[burn], AL_PITCH, 1); 
	alSourcef(source[burn], AL_GAIN, 1);
	alSourcefv(source[burn], AL_POSITION, source_pos);
	alSourcefv(source[burn], AL_VELOCITY, source_vel);
	alSourcei(source[burn], AL_LOOPING, AL_FALSE);

	//prehraje zvuk
	alSourcePlay(source[burn]);
	
	if (alGetError() != AL_NO_ERROR)
		return error_message("error playing burn sound"); 
}

int sound::play_wind(dragon& dr)
{
	//hodnoty pro posluchace a zdroje
	ALfloat source_pos[] = { 0, 0, 0 };
	ALfloat source_vel[] = { 0, 0, 0 };
	ALfloat listener_pos[] = { dr.pos.x, dr.pos.y, dr.pos.z };
	ALfloat listener_vel[] = { dr.spd.x, dr.spd.y, dr.spd.z };
	ALfloat listener_ori[] = { 0, 0, -1, 0, 1, 0 };

	//nastavi vlastnosti posluchace
	alListenerfv(AL_POSITION, listener_pos);
	alListenerfv(AL_VELOCITY, listener_vel);
	alListenerfv(AL_ORIENTATION, listener_ori);
	
	alGenSources(1, &(source[wind]));

	//nastavi vlastnosti zdroje zvuku
	alSourcei(source[wind], AL_BUFFER, buffer[wind]);
	alSourcef(source[wind], AL_PITCH, 0.8); 
	alSourcef(source[wind], AL_GAIN, 0.5);
	alSourcefv(source[wind], AL_POSITION, source_pos);
	alSourcefv(source[wind], AL_VELOCITY, source_vel);
	alSourcei(source[wind], AL_LOOPING, AL_TRUE);

	//prehraje zvuk
	alSourcePlay(source[wind]);
	
	if (alGetError() != AL_NO_ERROR)
		return error_message("error playing wind sound"); 
}

int sound::play_rain(dragon& dr)
{
	//hodnoty pro posluchace a zdroje
	ALfloat source_pos[] = { 0, 0, 0 };
	ALfloat source_vel[] = { 0, 0, 0 };
	ALfloat listener_pos[] = { dr.pos.x, dr.pos.y, dr.pos.z };
	ALfloat listener_vel[] = { dr.spd.x, dr.spd.y, dr.spd.z };
	ALfloat listener_ori[] = { 0, 0, -1, 0, 1, 0 };

	//nastavi vlastnosti posluchace
	alListenerfv(AL_POSITION, listener_pos);
	alListenerfv(AL_VELOCITY, listener_vel);
	alListenerfv(AL_ORIENTATION, listener_ori);
	
	alGenSources(1, &(source[rain]));

	//nastavi vlastnosti zdroje zvuku
	alSourcei(source[rain], AL_BUFFER, buffer[rain]);
	alSourcef(source[rain], AL_PITCH, 0.4); 
	alSourcef(source[rain], AL_GAIN, 0.1);
	alSourcefv(source[rain], AL_POSITION, source_pos);
	alSourcefv(source[rain], AL_VELOCITY, source_vel);
	alSourcei(source[rain], AL_LOOPING, AL_TRUE);

	//prehraje zvuk
	alSourcePlay(source[rain]);
	
	if (alGetError() != AL_NO_ERROR)
		return error_message("error playing rain sound"); 
}

void sound::finish()
{
	for (int i = 0;i < files_count;++i) {
		alDeleteBuffers(1, &buffer[i]);
		alDeleteSources(1, &source[i]);
	}
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);

	buffer.clear();
	source.clear();
}

