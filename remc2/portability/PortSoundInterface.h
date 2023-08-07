#pragma once

#ifndef PORT_SOUND_INTERFACE
#define PORT_SOUND_INTERFACE

#include <cstdint>
#include "../engine/Sound.h"
#include "../engine/global_types.h"
#include "../engine/ail_sound.h"

class PortSoundInterface
{
public:
	virtual ~PortSoundInterface() {}
	virtual int32_t ac_sound_call_driver(AIL_DRIVER* drvr, int32_t fn, VDI_CALL* out);
	virtual void ac_set_real_vect(uint32_t vectnum, uint16_t real_ptr);
	virtual uint16_t ac_get_real_vect(uint32_t vectnum);
	virtual void InitSample(HSAMPLE S);
	virtual void InitMIDISequence(uint8_t* datax, type_E3808_music_header* headerx, int32_t track_number);
	virtual void StartSample(HSAMPLE S);
	virtual void EndSample(HSAMPLE S);
	virtual void StartSequence(int32_t sequence_num);
	virtual void PauseSequence(int32_t sequence_num);
	virtual void StopSequence(int32_t sequence_num);
	virtual void ResumeSequence(int32_t sequence_num);
	virtual uint32_t SampleStatus(HSAMPLE S);
	virtual void SetSampleVolume(HSAMPLE S, int32_t volume);
	virtual void SetSequenceVolume(int32_t volume, int32_t milliseconds);
	virtual void SetLocation(axis_3d* coord, axis_4d* orient);
	virtual void EnableScheduling(void);
	virtual void SetMasterVolume(int32_t volume);
	virtual void Update();
	virtual void StartSpeech(const uint8_t track, const uint16_t offset, const uint16_t len);
	virtual void StartSpeech(const uint8_t track, const uint16_t offset, const uint16_t len, std::function<void(int16_t chunkId, uint16_t flags)> sampleEndedEventHandler);
	virtual void Finalize(int channel);
};

#endif //PORT_SOUND_INTERFACE
