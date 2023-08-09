#pragma once
#ifndef PORT_SDL_SOUND_H
#define PORT_SDL_SOUND_H

#include <filesystem>
#include <fcntl.h>
#include <time.h>
#include <string>
#include "xmi2mid.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "PortSoundInterface.h"
#include "../engine/Type_E3808_MusicHeader.h"
#include "../engine/engine_support.h"
#include "port_filesystem.h"


class port_sdl_sound : public PortSoundInterface
{
protected:
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

	bool InitSound();
	void CleanUpSound();

public:
	port_sdl_sound(bool hqsound, bool fixspeedsound, bool oggmusic, bool oggmusicalternative, std::string oggmusicFolder, std::string speech_folder);
	~port_sdl_sound();
	int32_t ac_sound_call_driver(AIL_DRIVER* drvr, int32_t fn, VDI_CALL* out);
	void ac_set_real_vect(uint32_t vectnum, uint16_t real_ptr);
	uint16_t ac_get_real_vect(uint32_t vectnum);
	void InitSample(HSAMPLE S);
	void InitMIDISequence(uint8_t* datax, type_E3808_music_header* headerx, int32_t track_number);
	void StartSample(HSAMPLE S);
	void EndSample(HSAMPLE S);
	void StartSequence(int32_t sequence_num);
	void PauseSequence(int32_t sequence_num);
	void StopSequence(int32_t sequence_num);
	void ResumeSequence(int32_t sequence_num);
	uint32_t SampleStatus(HSAMPLE S);
	void SetSampleVolume(HSAMPLE S, int32_t volume);
	void SetSequenceVolume(int32_t volume, int32_t milliseconds);
	void SetLocation(axis_3d* coord, axis_4d* orient);
	void EnableScheduling(void);
	void SetMasterVolume(int32_t volume);
	void Update();
	void StartSpeech(const uint8_t track, const uint16_t offset, const uint16_t len);
	void StartSpeech(const uint8_t track, const uint16_t offset, const uint16_t len, std::function<void(int16_t chunkId, uint16_t flags)> sampleEndedEventHandler);
	void DeleteSource(uint16_t channel);
	void Finalize(int channel);
};
#endif                          //PORT_SDL_SOUND
