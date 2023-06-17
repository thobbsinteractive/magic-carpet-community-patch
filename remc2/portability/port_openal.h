#pragma once
#ifndef PORT_OPENAL_H
#define PORT_OPENAL_H

#include "AL/al.h"

#define   OPENAL_CHANNELS  24
#define       OPENAL_C_SZ  OPENAL_CHANNELS     ///< number of chunks that can play at the same time (aka number of voices)
#define      OPENAL_CC_SZ  128     ///< number of chunks the cache can hold

////< flags used by alsound_set_env()
#define       AL_SET_BANK  0x1

#define   AL_BANK_MAP_DAY  0x0
#define AL_BANK_MAP_NIGHT  0x1
#define  AL_BANK_MAP_CAVE  0x2
#define      AL_BANK_MENU  0x4

#define   AL_FORMAT_STEREO8_22050  0x01
#define     AL_FORMAT_MONO8_22050  0x02
#define  AL_FORMAT_STEREO16_44100  0x04
#define               AL_TYPE_ENV  0x08
#define        AL_TYPE_POSITIONAL  0x10
#define            AL_TYPE_SPEECH  0x20
#define          AL_IGNORE_RECODE  0x40

#define          AL_REPLAY_RARELY  0x01 // long intervals of silence
#define      AL_REPLAY_FREQUENTLY  0x02 // short intervals of silence
#define         AL_POWERFUL_SHOUT  0x04 // controls the reference distance and gain
#define                AL_WHISPER  0x08 // controls the reference distance and gain

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

void alsound_init(void);
int16_t alsound_play(const int16_t chunk_id, Mix_Chunk *chunk, event_t *entity,
                     al_ssp_t *ssp, const uint16_t flags);
void alsound_update(void);
void alsound_clear_cache(void);
void alsound_close(void);
void alsound_set_env(const int32_t value, const uint8_t flag);
void alsound_set_location(axis_3d *coordinates, axis_4d *orientation);
void alsound_end_sample(const int32_t chunk_id);
uint8_t alsound_sample_status(const int32_t chunk_id);
void alsound_set_sample_volume(const int32_t chunk_id, const int32_t volume);
uint16_t alsound_get_chunk_flags(const int16_t chunk_id);
int16_t alsound_create_source(const int16_t chunk_id, al_ssp_t *ssp, event_t *entity);
void alsound_update_source(event_t *entity);
void alsound_delete_source(const int16_t ch);
void alsound_enable_scheduling(void);
uint8_t alsound_save_chunk(uint8_t *data, const uint32_t len, char *filename);

void alsound_imgui(bool *p_open);

#endif
