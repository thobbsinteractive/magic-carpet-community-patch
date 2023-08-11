#pragma once
#ifndef PORT_OPENAL_H
#define PORT_OPENAL_H

#include "AL/al.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include "AL/efx.h"
#include "AL/efx-presets.h"
#include "port_sdl_sound.h"
#include "port_sound_lut.h"
#include "../engine/Sound.h"

struct al_sound_source_parameters {
    float gain;
    float reference_distance;
    float max_distance;
    float rolloff_factor;
    axis_3d coord;
    axis_4d orient;
};
typedef struct al_sound_source_parameters al_ssp_t;

typedef struct _str_0x6E8E event_t;

struct al_chunk {
	int16_t id;                 ///< chunk identifier
	ALint state;                ///< 0, AL_PLAYING or something in between
	ALuint alSource;            ///< openal source identifier
	ALsizei size;               ///< chunk size
	event_t* entity;            ///< what entity has created the sound source
	uint16_t flags;
};
typedef struct al_chunk al_chunk_t;     ///< element of the currently playing chunks array

struct al_chunk_cache {
	int16_t id;                 ///< chunk identifier
	uint16_t flags;             ///< 0 or OPENAL_FLG_LOADED
	ALuint bufferName;          ///< openal buffer identifier
	ALsizei size;               ///< chunk size
};
typedef struct al_chunk_cache al_chunk_cache_t; ///< element of the cached chunks array

struct al_env {
	uint8_t initialized;        ///< '1' if the OpenAL-soft library was properly initialized
	uint8_t efx_initialized;    ///< '1' if the ALC_EXT_EFX extension is usable
	uint8_t scheduling_enabled; ///< state of the chunk scheduling
	int8_t bank;                ///< current sound bank
	int8_t reverb_type;         ///< should match the current MapType
	uint32_t frame_cnt;         ///< frame counter
	axis_3d listener_c;         ///< the listener's coordinates in game space (x, y, z)
	axis_4d listener_o;         ///< the listener's orientation values (yaw, pitch, roll)
};
typedef struct al_env al_env_t; ///< random collection of global variables

struct al_next_vol {            ///< sometimes the volume of a chunk is received before the chunk itself, so keep that info here
	int16_t chunk_id;           ///< chunk identifier
	float gain;                 ///< volume (0-127) converted into gain (0-1.0)
};
typedef struct al_next_vol al_next_vol_t;

class port_openal : public port_sdl_sound
{
private:
	void alsound_cache(const int16_t cache_ch, const int16_t chunk_id, const Mix_Chunk* mixchunk, const uint16_t flags);
	ALuint alsound_load_effect(const EFXEAXREVERBPROPERTIES* reverb);
	const char* alsound_get_error_str(ALCenum error);
	ALCenum alsound_error_check(const char* msg);

public:
	port_openal(bool hqsound, bool fixspeedsound, bool oggmusic, bool oggmusicalternative, std::string oggmusicFolder, std::string speech_folder);

	bool InitSound() override;
	void CleanUpSound() override;
	void InitSample(HSAMPLE S) override;
	void StartSpeech(const uint8_t track, const uint16_t offset, const uint16_t len) override;
	void StartSpeech(const uint8_t track, const uint16_t offset, const uint16_t len, std::function<void(int16_t chunkId, uint16_t flags)> sampleEndedEventHandler) override;
	void SetMasterVolume(int32_t volume) override;
	void SetSampleVolume(HSAMPLE S, int32_t volume) override;
	void StartSample(HSAMPLE S) override;
	void EndSample(HSAMPLE S) override;
	uint32_t SampleStatus(HSAMPLE S) override;
	void Update() override;
	void DeleteSource(uint16_t ch) override;
	void EnableScheduling(void) override;
	void SetLocation(axis_3d* coordinates, axis_4d* orientation) override;

	void alsound_init(void);
	int16_t alsound_play(const int16_t chunk_id, Mix_Chunk* chunk, event_t* entity, al_ssp_t* ssp, const uint16_t flags);
	int16_t alsound_play(const int16_t chunk_id, Mix_Chunk* chunk, event_t* entity, al_ssp_t* ssp, const uint16_t flags, std::function<void(int16_t chunkId, uint16_t flags)> sampleEndedEventHandler);
	void alsound_update(void);
	void alsound_clear_cache(void);
	void alsound_close(void);
	void alsound_set_env(const int32_t value, const uint8_t flag);
	void alsound_end_sample(const int32_t chunk_id);
	int16_t alsound_find_alc_sample(const int32_t id);
	std::vector<int16_t> alsound_get_current_playing_samples_by_flags(uint16_t flags);
	uint8_t alsound_sample_status(const int32_t chunk_id);
	void alsound_set_sample_volume(const int32_t chunk_id, const int32_t volume);
	uint16_t alsound_get_chunk_flags(const int16_t chunk_id);
	int16_t alsound_create_source(const int16_t chunk_id, al_ssp_t* ssp, event_t* entity);
	void alsound_update_source(event_t* entity);
	uint8_t alsound_save_chunk(uint8_t* data, const uint32_t len, char* filename);
	void alsound_set_master_volume(int32_t volume);
	void alsound_imgui(bool* p_open);
};
#endif //PORT_OPENAL_H