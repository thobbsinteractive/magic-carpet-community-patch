#pragma once
#ifndef PORT_SDL_SOUND_H
#define PORT_SDL_SOUND_H

#define SOUND_OPENAL

#include <filesystem>
#include "mctypes.h"

#define SOUND_SDLMIXER

#ifdef _MSC_VER
	#include "SDL2/SDL.h"
#ifdef SOUND_SDLMIXER
	#include "SDL2/SDL_mixer.h"
#endif
#else
#include "SDL2/SDL.h"
#ifdef SOUND_SDLMIXER
#include "SDL2/SDL_mixer.h"
#endif
#endif

//#include "music_timidity.h"
#include "xmi2mid.h"
#include <time.h>               /* time */
#include <string>

#include "../engine/ail_sound.h"
#include "port_filesystem.h"

#pragma pack (1)
typedef struct {                //length 32
    int8_t filename_14[18];
    uint8_t *wavData_0;
    int8_t stub_4[4];
    int32_t wavSize_8;
    int16_t word_12;
} sub2type_E37A0_sound_buffer2;

typedef struct {                //length 3072
    sub2type_E37A0_sound_buffer2 wavs_10[96];
} sub1type_E37A0_sound_buffer2;

typedef struct {                //length 3090
    int8_t byte_0;
    int8_t byte_1;
    int8_t byte_2;
    int8_t byte_3;
    int8_t byte_4;
    int8_t byte_5;
    int8_t byte_6;
    int8_t byte_7;
    sub1type_E37A0_sound_buffer2 str_8; //3072 length
    int8_t next_str[10];
} type_E37A0_sound_buffer2;

//shadow type_E37A0_sound_buffer2
typedef struct {                //length 32
    int8_t filename_14[18];
    int32_t wavData_0;
    int8_t stub_4[4];
    int32_t wavSize_8;
    int16_t word_12;
} shadow_sub2type_E37A0_sound_buffer2;

typedef struct {                //length 3072
    shadow_sub2type_E37A0_sound_buffer2 wavs_10[96];
} shadow_sub1type_E37A0_sound_buffer2;

typedef struct {                //length 3090
    int8_t byte_0;
    int8_t byte_1;
    int8_t byte_2;
    int8_t byte_3;
    int8_t byte_4;
    int8_t byte_5;
    int8_t byte_6;
    int8_t byte_7;
    shadow_sub1type_E37A0_sound_buffer2 str_8;  //3072 length
    int8_t next_str[10];
} shadow_type_E37A0_sound_buffer2;

typedef struct {                //length 16*6=96
    int32_t dword_0;
    int32_t dword_4;
    int32_t sizeBytes_8;
    int32_t dword_12;
} type_v8;

typedef struct {                //length 32 - this is may be format of wav sound file
    uint8_t *xmiData_0;         //data of wav//18
    int8_t stub_4[4];           //22
    int32_t xmiSize_8;          //24
    int16_t word_12;            //28
    int8_t filename_14[18];     //first 18 chars - name//30
} sub2type_E3808_music_header;

typedef struct {                //length 216
    int8_t stub[10];
    sub2type_E3808_music_header track_10[6];
    int8_t stubb[14];
} sub1type_E3808_music_header;

typedef struct {                //length 224
    int8_t byte_0;
    int8_t byte_1;
    int8_t byte_2;
    int8_t byte_3;
    int8_t byte_4;
    int8_t byte_5;
    int8_t byte_6;
    int8_t byte_7;
    sub1type_E3808_music_header str_8;  //216 length
} type_E3808_music_header;
/*
typedef struct {//length 80656
	int8_t byte_0;
	int8_t byte_1;
	int8_t byte_2;
	int8_t byte_3;
	int8_t byte_4;
	int8_t byte_5;
	int8_t byte_6;
	int8_t byte_7;
	int8_t data_8[];
}
type_E3810_music_data;*/

//shadow shadow_type_E3808_music_header
typedef struct {                //length 32 - this is may be format of wav sound file
    int32_t xmiData_0;          //data of wav//18
    int8_t stub_4[4];           //22
    int32_t xmiSize_8;          //24
    int16_t word_12;            //28
    int8_t filename_14[18];     //first 18 chars - name//30
} shadow_sub2type_E3808_music_header;

typedef struct {                //length 216
    int8_t stub[10];
    shadow_sub2type_E3808_music_header track_10[6];
    int8_t stubb[14];
} shadow_sub1type_E3808_music_header;

typedef struct {                //length 224
    int8_t byte_0;
    int8_t byte_1;
    int8_t byte_2;
    int8_t byte_3;
    int8_t byte_4;
    int8_t byte_5;
    int8_t byte_6;
    int8_t byte_7;
    shadow_sub1type_E3808_music_header str_8;   //216 length
} shadow_type_E3808_music_header;
#pragma pack (16)

#define USE_SDL2

#define DEBUG_SOUND
class port_sdl_sound
{

private:
	bool m_hqsound = false;
	bool m_oggmusic = false;
	std::string m_oggmusicFolder;
	bool m_oggmusicalternative;
	std::string m_speech_folder;
	bool m_fixspeedsound;
	int32_t m_last_sequence_num = 0;
	int m_lastMusicVolume = -1;
	int m_settingsMusicVolume = 127;
	int m_num_IO_configurations = 3;
	int m_service_rate = -1;
	int m_master_volume = -1;

	uint8_t m_sound_buffer[4][20000];
	HSAMPLE m_gamechunkHSAMPLE[32];   //OPENAL_CHANNELS];
	Mix_Chunk m_gamechunk[32];        //OPENAL_CHANNELS];
	uint16_t m_actvect[4096];

	Mix_Music* m_GAME_music[20] =
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL
	};

	struct {
		int a;
	} common_IO_configurations;

	struct {
		int a;
	} environment_string;

public:
	port_sdl_sound(bool hqsound, bool fixspeedsound, bool oggmusic, bool oggmusicalternative, std::string oggmusicFolder, std::string speech_folder);
	~port_sdl_sound();
	bool init_sound();
	void clean_up_sound();
	void playmusic2(int32_t track_number);
	int32_t ac_sound_call_driver(AIL_DRIVER* drvr, int32_t fn, VDI_CALL* out);
	void ac_set_real_vect(uint32_t vectnum, uint16_t real_ptr);
	uint16_t ac_get_real_vect(uint32_t vectnum);
	AIL_DRIVER* ac_AIL_API_install_driver(int a1, uint8_t* a2, int a3);
	void SOUND_init_MIDI_sequence(uint8_t* datax, type_E3808_music_header* headerx, int32_t track_number);
	void SOUND_start_sample(HSAMPLE S);
	void SOUND_end_sample(HSAMPLE S);
	void SOUND_start_sequence(int32_t sequence_num);
	void SOUND_pause_sequence(int32_t sequence_num);
	void SOUND_stop_sequence(int32_t sequence_num);
	void SOUND_resume_sequence(int32_t sequence_num);
	uint32_t SOUND_sample_status(HSAMPLE S);
	void SOUND_set_sample_volume(HSAMPLE S, int32_t volume);
	void SOUND_set_sequence_volume(int32_t volume, int32_t milliseconds);
	void SOUND_set_master_volume(int32_t volume);
	void SOUND_UPDATE();
	void SOUND_start_speech(const uint8_t track, const uint16_t offset, const uint16_t len);
	void SOUND_start_speech(const uint8_t track, const uint16_t offset, const uint16_t len, std::function<void(int16_t chunkId, uint16_t flags)> sampleEndedEventHandler);
	void SOUND_finalize(int channel);
};
#endif                          //PORT_SDL_SOUND
