
#define _CRT_SECURE_NO_WARNINGS


#include"Music.h"
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

#include"gazou.h"

Music music;
Music touch;

enum {
	MONO = 1,
	STEREO
};

Music::Music(char*filename)
{
	LoadMusic(filename);
}

Music::Music(char*filename, char*musicname, char*_bpmfile, char*jakettoname, char*titlejakename, float _bpm){
	memset( name, 0, sizeof(char)*32 );
	strcpy(name, musicname);
	bpmfile = load_gazou(_bpmfile);
	LoadMusic(filename);
	jaketto = load_gazou(jakettoname);
	title_music = load_gazou(titlejakename);
	bpm = _bpm;
}

void Music::LoadMusic(char*filename){
	ALCdevice *device = alcOpenDevice(NULL);
	assert(device != NULL);

	ALCcontext *context = alcCreateContext(
		device, // ALCdevice *device
		NULL);  // const ALCint* attrlist
	assert(context != NULL);

	alcMakeContextCurrent(context);// ALCcontext *context
	assert(alGetError() == AL_NO_ERROR);


	alGenBuffers(
		1,      // ALsizei n
		&buffer);  // ALuint* buffers
	assert(alGetError() == AL_NO_ERROR);

	MYWAVEFORMAT wavfmt;


	assert(alGetError() == AL_NO_ERROR);


	FILE *pFile = fopen(
		filename,
		"rb");

	assert(pFile != NULL);

	fread(
		&wavfmt,
		sizeof(MYWAVEFORMAT),
		1,
		pFile);

	int w_size = wavfmt.data_size;
	w_data = (unsigned char *)malloc(sizeof(char)*w_size);
	memset(w_data, 0, sizeof(char)*w_size);

	fread(
		w_data,
		wavfmt.data_size,
		1,
		pFile);

	int format;
	if (wavfmt.channel == MONO)
	{
		if (wavfmt.bit == 8) 
		{
			format = AL_FORMAT_MONO8;
		}
		else if (wavfmt.bit == 16)
		{
			format = AL_FORMAT_MONO16;
		}
	}
	else if (wavfmt.channel == STEREO) 
	{
		if (wavfmt.bit == 8)
		{
			format = AL_FORMAT_STEREO8;
		}
		else if (wavfmt.bit == 16)
		{
			format = AL_FORMAT_STEREO16;
		}
	}


	

	alBufferData(
		buffer,            // ALuint bid
		format,// ALenum format
		w_data,        // const ALvoid* data
		w_size,           // ALsizei size
		wavfmt.rate);      // ALsizei freq

	assert(alGetError() == AL_NO_ERROR);

	alGenSources(
		1,      // ALsizei n
		&source);  // ALuint* sources

	assert(alGetError() == AL_NO_ERROR);

	alSourcei(
		source,        // ALuint sid
		AL_BUFFER,  // ALenum param
		buffer);       // ALint value


	assert(alGetError() == AL_NO_ERROR);

	free(w_data);

	fclose(pFile);

}

