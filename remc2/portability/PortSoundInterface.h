#pragma once

#ifndef PORT_SOUND_INTERFACE
#define PORT_SOUND_INTERFACE

#include <functional>
#include "../engine/global_types.h"
#include "../engine/ail_sound.h"
#include "../engine/Type_E3808_MusicHeader.h"

////< flags used by alsound_set_env()
#define	AL_SET_BANK					0x1

#define	AL_BANK_MAP_DAY				0x0
#define	AL_BANK_MAP_NIGHT			0x1
#define	AL_BANK_MAP_CAVE			0x2
#define	AL_BANK_MENU				0x4

#define	AL_FORMAT_STEREO8_22050		0x01
#define	AL_FORMAT_MONO8_22050		0x02
#define	AL_FORMAT_STEREO16_44100	0x04
#define	AL_TYPE_ENV					0x08
#define	AL_TYPE_POSITIONAL			0x10
#define	AL_TYPE_SPEECH				0x20
#define	AL_IGNORE_RECODE			0x40

#define	AL_REPLAY_RARELY			0x01 // long intervals of silence
#define	AL_REPLAY_FREQUENTLY		0x02 // short intervals of silence
#define	AL_POWERFUL_SHOUT			0x04 // controls the reference distance and gain
#define	AL_WHISPER					0x08 // controls the reference distance and gain

class PortSoundInterface
{
public:
	virtual int32_t ac_sound_call_driver(AIL_DRIVER* drvr, int32_t fn, VDI_CALL* out) = 0;
	virtual void ac_set_real_vect(uint32_t vectnum, uint16_t real_ptr) = 0;
	virtual uint16_t ac_get_real_vect(uint32_t vectnum) = 0;
	virtual bool InitSound() = 0;
	virtual void CleanUpSound() = 0;
	virtual void InitSample(HSAMPLE S) = 0;
	virtual void InitMIDISequence(uint8_t* /*datax */, type_E3808_music_header* headerx, int32_t track_number) = 0;
	virtual void StartSample(HSAMPLE S) = 0;
	virtual void EndSample(HSAMPLE S) = 0;
	virtual void StartSequence(int32_t sequence_num) = 0;
	virtual void PauseSequence(int32_t sequence_num) = 0;
	virtual void StopSequence(int32_t sequence_num) = 0;
	virtual void ResumeSequence(int32_t sequence_num) = 0;
	virtual uint32_t SampleStatus(HSAMPLE S) = 0;
	virtual void SetSampleVolume(HSAMPLE S, int32_t volume) = 0;
	virtual void SetSequenceVolume(int32_t volume, int32_t milliseconds) = 0;
	virtual void SetLocation(axis_3d* coord, axis_4d* orient) = 0;
	virtual void EnableScheduling(void) = 0;
	virtual void SetMasterVolume(int32_t volume) = 0;
	virtual void Update() = 0;
	virtual void StartSpeech(const uint8_t track, const uint16_t offset, const uint16_t len) = 0;
	virtual void StartSpeech(const uint8_t track, const uint16_t offset, const uint16_t len, std::function<void(int16_t chunkId, uint16_t flags)> sampleEndedEventHandler) = 0;
	virtual void DeleteSource(uint16_t channel) = 0;
};

#endif //PORT_SOUND_INTERFACE
