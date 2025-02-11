#pragma once

#include "ail_sound.h"
#include "Basic.h"
#include "../utilities/Wave.h"
#include "../engine/CommandLineParser.h"
#include "../portability/port_show_perifery.h"

#pragma pack (1)
typedef struct {//lenght 12
	int16_t word_0;
	int16_t word_1;
	int16_t word_2;
	int16_t word_3;
	int16_t word_4;
	int16_t word_5;
}type_F4FE0;

typedef struct {
	int32_t par1;
	int16_t par2;
} type_str_32_16; // weak
#pragma pack (16)

extern bool soundActive_E3799;
extern bool musicActive_E37FD;
extern bool soundAble_E3798;
extern bool musicAble_E37FC;
extern int x_DWORD_E3844;
extern int x_DWORD_E387C;
extern FILE* x_FILE_E3840;
extern __int16 m_iNumberOfTracks;
extern int x_DWORD_E387C;
extern int8_t soundActiveL_E2A14;
extern int8_t soundActiveH_E2A14;
extern __int16 soundFreqType_E37B6;
extern bool autoScanForSoundHardware_E379B;
extern __int16 x_WORD_E3828;
extern int x_DWORD_E3824;
extern __int16 x_WORD_E381C;
extern __int16 x_WORD_E381E;
extern __int16 x_WORD_E3820;
extern __int16 x_WORD_E3822;
extern __int16 x_WORD_E387A;
extern __int16 x_WORD_E387A;
extern int x_DWORD_E383C;
extern __int16 x_WORD_E3834;
extern type_E3808_music_header* musicHeader_E3808;
extern char musicDriverType_180C84;
extern int16_t x_WORD_181B44;
extern char x_BYTE_E2A28_speek; // weak
extern type_F4FE0 str_F4FE0[70];

extern uint8_t* x_DWORD_182188[];
extern uint8_t* x_DWORD_1821A0[];
extern uint8_t* x_DWORD_1821B8[];
extern uint8_t* x_DWORD_1821D0[];
extern uint8_t* x_DWORD_1821E8[];

void InitSound_8D290();
void sub_8D800_sound_proc2();
void EndSample_8D8F0();
void InitMusic_8D970();
void StopMusic_8E020();
int sub_8E0D0();
void StartMusic_8E160(int track, int volume);
void sub_8E410_sound_proc16_xmidivolume(int master_volume);
void sub_8E470_sound_proc17_volume(int volume);
bool InitMusicBank_8EAD0(int channel);
void GetMusicSequenceCount();
bool LoadMusicTrack(FILE* filehandle, uint8_t drivernumber);
int sub_8F0AB(FILE* a1, int a3);
void sub_8F100_sound_proc19(uint32_t a1, __int16 index, int volume, int a4, unsigned __int16 a5, char a6, unsigned __int8 a7);
void sub_8F420_sound_proc20(int a1, __int16 a2);
void sub_8F710_sound_proc21(int flags, __int16 index, int loopCount, unsigned __int8 initTimers, char volScale);
void StopTimer_8F850();
void InitSoundAndMusic_90FD0();
void InitAWE32orMPU401_91010();
void sub_91420();
bool DebugSoundTimer_916F0();
void AilShutdown_919C0();
void AilSetPreference_91A80(uint32_t number, int32_t value);
void PlusE3FF2_91BD0();
void MinusE3FF2_91BF0();
uint16_t AilApiGetRealVect_A121D(uint32_t vectnum);
void AilSetRealVect_91D50(uint32_t vectnum, uint16_t real_ptr);
void AilRestoreUSE16ISR_91E90(int32_t isr);
void EndSounds_99C10();
void sub_99C90();
HDIGDRIVER AilInstallDigDriverFile_93330(char* filename, IO_PARMS* IO);
char sub_9AE90(int eax0, int edx0, char* ebx0, int* a1, int8_t* a2, int a3, int a4);
int AilInstallDigIni_931F0(HDIGDRIVER* a2, char* digPath);
HMDIDRIVER AilInstakkMidiDriverFile_95850(char* filename, IO_PARMS* IO);
int32_t AilInstallMidiIni_95710(HMDIDRIVER* mdi, char* fileName);
void AilDelay_920D0(int a1);
int sub_92160();
bool AilReadIniFile_92190(AIL_INI* INI, char* filename);
IO_PARMS* AilGetIoEnvironment_92ED0(AIL_DRIVER* drvr);
AIL_DRIVER* AilInstallDriver_93010(uint8_t* driver_image, int32_t n_bytes);//274010
int AilUninstallDriver_93160(AIL_DRIVER* ailDriver);
int AilUninstallDigDriver_93480(HDIGDRIVER hDigDriver);
HSAMPLE AilAllocateSampleHandle_93510(HDIGDRIVER hDigDriver);
void AilInitSample_93830(HSAMPLE sample);
int32_t AilSetSampleFile_938C0(HSAMPLE S, uint8_t* pWaveData, int32_t block);
void AilSetSampleAddress_93A10(HSAMPLE S, uint8_t* start, uint32_t len);
void AilStartSample_93B50(HSAMPLE S);
void AilEndSample_93D00(HSAMPLE S);
void AilSetSamplePlaybackRate_93D90(HSAMPLE S, int32_t playback_rate);
void AilSetSampleVolume_93E30(HSAMPLE S, int32_t volume);
void AilSetSampleVolumePan_93ED0(HSAMPLE S, int32_t volume);
void AilSetSampleLoopCount_93F70(HSAMPLE S, int loop_count);
uint32_t AilSampleStatus_94010(HSAMPLE S);
void AilDigitalMasterVolume_94650(int master_volume);
EOS_callback_type AilRegisterEosCallback_95140(HSAMPLE sample, EOS_callback_type a2);
void AilSetSampleUserData_953E0(HSAMPLE S, int a2, int a3);
int AilSampleUserData_95480(HSAMPLE S, int a2);
int AilUninstallMidiDriver_959A0(HMDIDRIVER  mdi);
HSEQUENCE AilAllocateSequenceHandle_95A30(HMDIDRIVER mdi);
int32_t AilInitSequence_95C00(HSEQUENCE hSequence, uint8_t* start, int32_t sequence_num, uint32_t track);
void AilStartSequence_95D50(HSEQUENCE hSequence, uint32_t track);
void AilStopSequence_95DE0(HSEQUENCE hSequence);
void sub_95E70_AIL_resume_sequence(HSEQUENCE hSequence);
void AilEndSequence_95F00(HSEQUENCE hSequence);
void AilSetSequenceVolume_96030(int32_t volume, int32_t milliseconds);
int AilSequenceStatus_96170(HSEQUENCE hSequence);
void AilSetXMidiMasterVolume_96670(int32_t master_volume);
int32_t sub_969A0_AIL_MDI_driver_type(HMDIDRIVER mdi);
void AilSetGtlFilenamePrefix_96AE0(char* samplePath);
void AilSequencePosition_97330(HSEQUENCE hSequence, x_DWORD* a2, x_DWORD* a3);
void AilBranchIndex_97480(HSEQUENCE hSequence, int a2);
void AilRegisterTriggerCallback_97670(HSEQUENCE hSequence, xCALLBACK a2);
int AilLockChannel_97F90(MDI_DRIVER* a1);
void AilReleaseChannel_980D0(HMDIDRIVER mdi, int a2);
void AilMapSequenceChannel_98170(HSEQUENCE a1, int a2, int a3);
void AilSendChannelVoiceMessage_98360(HMDIDRIVER mdi, HSEQUENCE hSequence, int32_t status, int32_t data_1, int32_t data_2);
bool LoadSound_84300(uint8_t soundIndex);
void LoadSoundDataFromBuffer_844A0(uint16_t count);
bool ReadAndDecompressSound(FILE* file, uint8_t soundIndex2);
bool AilApiReadIni_9E3A0(AIL_INI* INI, char* filename);
void AilSetPreference_9E6E0(uint32_t number, int32_t value);
AIL_DRIVER* AilApiInstallDriver_9E720(uint8_t* driver_image, int32_t n_bytes);//27f720
int AilApiUninstallDriver_9EA60(AIL_DRIVER* ailDriver);
IO_PARMS* AilApiGetIoEnvironment_9EB60(AIL_DRIVER* drvr);
void sub_9EC30();
void UninstallDrivers_9ED70();
int sub_9EE70();
void sub_9F040();
void sub_9FA80();
void InitAWE32_9F740(char* a1);
int sub_9F280(HMDIDRIVER hMdiDriver);
VDI_CALL sub_9F2E0(HMDIDRIVER hMdiDriver, int a2, unsigned __int16 a3, unsigned __int16 a4);
__int64 sub_9F3D0(HMDIDRIVER hMdiDriver, int a2, unsigned __int16 a3, unsigned __int16 a4);
VDI_CALL sub_9F4F0(HMDIDRIVER hMdiDriver, int a2, unsigned __int16 a3, unsigned __int16 a4);
VDI_CALL sub_9F5E0(HMDIDRIVER hMdiDriver, int a2, unsigned __int16 a3, unsigned __int16 a4);
VDI_CALL sub_9F6D0(HMDIDRIVER hMdiDriver, __int16 a2);
void PlusE3FF2_A0EEC();
void MinusE3FF2_A0EF9();
char sub_A102C(int a1);
char sub_A105C(unsigned int a1);
void sub_A108F();
void sub_A10F4_sound_proc_irq();
void sub_A11E2();
void AilApiSetRealVect_A1249(uint32_t vectnum, uint16_t real_ptr);
void AilApiRestoreUSE16IISR_A14DB(int isr);
unsigned int sub_A1520();
void sub_A1524(unsigned int a1);
int32_t AilApiCallDriver_A158B(AIL_DRIVER* drvr, int32_t fn, VDI_CALL* in, VDI_CALL* out);
void AilApiDelay_A1665(int a1);
int GetE3FFE_A16A2();
void sub_A1798();
void sub_A2070(HDIGDRIVER a1);
void sub_A20D0(HDIGDRIVER a1);
void InitSampleVolume_A2110(HSAMPLE S);
bool sub_A2650(HDIGDRIVER digDriver);
int InitEnvs_A2C80(HDIGDRIVER a1, IO_PARMS* a2);
int sub_A2DE0();
HDIGDRIVER sub_A2EA0(AIL_DRIVER* a1, IO_PARMS IO);
int sub_A37A0(HDIGDRIVER a1);
HSAMPLE sub_A3820_allocate_sample_handle(HDIGDRIVER dig);
void InitSample_A38E0(HSAMPLE S);
void SetSampleAddress_A3A30(HSAMPLE S, uint8_t* start, uint32_t len);
void SetSampleType_A3A70(HSAMPLE S, int32_t a2, uint32_t a3);
void SetSamplePlaybackRate_A3AF0(HSAMPLE S, int32_t playback_rate);
int32_t GetSampleVolume_A3B10(HSAMPLE S);
void SetSampleVolume_A3B40(HSAMPLE S, int32_t volume);
int32_t GetSampleVolumePan_A3B80(HSAMPLE S);
void SetSampleVolumePan_A3BB0(HSAMPLE S, int32_t volume);
void SetSampleLoopCount_A3C90(HSAMPLE S, int loop_count);
void ApiAilStartSample_A3CB0(HSAMPLE S);
void ApiAilEndSample_A3DA0(HSAMPLE S);
EOS_callback_type RegisterEosCallback_A3EB0(HSAMPLE S, EOS_callback_type EOS);
void SetSampleUserData_A3F00(HSAMPLE S, int a2, int a3);
int SampleUserData_A3F30(HSAMPLE S, int index);
void SetDigitalMasterVolume_A3F70(HDIGDRIVER driver, int a2);
void sub_A43E0(HSAMPLE sample);
int sub_A47A0();
void SubSetSampleFile_A47C0(uint8_t* pWavData, HSAMPLE S);
int sub_A4920();
bool SetSampleFile_A4B20(HSAMPLE S, uint8_t* pWavData, int32_t block);
signed int sub_A4E10(char a1);
void sub_A4EB0(HMDIDRIVER a1);
void sub_A4F10(HMDIDRIVER a1, char a2, char a3, char a4);
void sub_A4FD0(HMDIDRIVER a1, int a2, unsigned int a3);
unsigned int sub_A50A0(int a1);
uint8_t* sub_A50F0(uint8_t* a1, int a2);
int sub_A5210(int a1, char a2, unsigned int a3);
void sub_A5530(CTRL_LOG* a1, char a2, unsigned int a3, unsigned __int8 a4);
void sub_A5850(HSEQUENCE hSequence, char a2, unsigned int a3, signed int a4, int a5);
void sub_A5E50(HSEQUENCE hSequence);
void sub_A5F30(HSEQUENCE hSequence, int a2);
void sub_A5FD0(HSEQUENCE a1, int a2);
void sub_A6370(HSEQUENCE hSequence);
void sub_A6490(HSEQUENCE hSequence);
void sub_A64C0(HSEQUENCE hSequence);
int SetIoParameters_A6E00(HMDIDRIVER a1, IO_PARMS* a2);
void sub_A6F30(void* a);
HMDIDRIVER InitAilDriver_A6FB0(AIL_DRIVER* a1, IO_PARMS* a2);
int sub_A7970_AIL_API_uninstall_MDI_driver(HMDIDRIVER mdi);
int32_t sub_A7990_AIL_API_MDI_driver_type(HMDIDRIVER mdi);
void AilApiSetGTLFilenamePrefix_A7AA0(char* samplePath);
HSEQUENCE AilApiAllocateSequenceHandle_A7B30(HMDIDRIVER mdi);
void sub_A7BF0_sound_proc33(HSEQUENCE hSequence);
int32_t AilApiInitSequence_A7C20(HSEQUENCE hSequence, void* start, int32_t sequence_num, uint32_t track);
void AilApiStartSequence_A8010(HSEQUENCE hSequence, uint32_t track);
void sub_A8050_AIL_API_stop_sequence(HSEQUENCE hSequence);
void sub_A8180_AIL_API_resume_sequence(HSEQUENCE hSequence);
void AilApiEndSequence_A8250(HSEQUENCE hSequence);
void AilAPISetSequenceVolume_A8360(HSEQUENCE hSequence, int32_t volume, int32_t milliseconds);
int AilApiSequenceStatus_A8410(HSEQUENCE hSequence);
void sub_A8830(HSEQUENCE hSequence, x_DWORD* a2, x_DWORD* a3);
void sub_A8900(HSEQUENCE hSequence, int marker);
void AilApiTriggerCallback_A8A20(HSEQUENCE hSequence, xCALLBACK callback);
int AilApiLockChannel_97F90_A8BF0(MDI_DRIVER* a1);
void sub_A8EA0(HMDIDRIVER mdi, int a2);
void sub_A9080(HSEQUENCE a1, int a2, int a3);
void AilAPISendChannelVoiceMessage_A9140(HMDIDRIVER mdi, HSEQUENCE hSequence, int32_t status, int32_t data_1, int32_t data_2);
int sub_A9C00();
int sub_A9C50();
int AilApiInstallDigINI_A3720(HDIGDRIVER* dig, char* digPath);
HDIGDRIVER AilApiInstallDigDriverFile_A3600(char* filename, IO_PARMS* IO);
int32_t AilApiInstallMDIIni_A78F0(HMDIDRIVER* mdi, char* fileName);
HMDIDRIVER AilApiInstallMDIIni_A77D0(char* filename, IO_PARMS* IO);
__int16 sub_98B2C(unsigned __int8 a1, int a2);
int StrToInt(const char* text, int maxDigits);
signed int AllocMem_9D4D0(int a1, uint8_t** a2, uint32_t* a3, uint32_t* a4);//27e4d0
void FreeMem_9D560(uint8_t* a1);
unsigned int sub_91F20();
signed __int64 sub_9F110(int a1);
int sub_9F170(int a1, unsigned __int16 a2);
int sub_9F1D0(int a1);
int sub_9F220(int a1);
void sub_99970(char a1, unsigned __int8 a2);
signed int sub_99E8E(char* a1, char** a2, signed int a3, int a4);
int sub_99FF5(unsigned __int8 a1);
void SetSoundFreq_9A230(int a1);
void WriteWaveToFile(wav_t* wav, const char* name);
void AIL_fix();
const char* mygetenv(const char* a1);
void PrepareEventSound_6E450(__int16 a1, __int16 a2, __int16 a3);
void ChangeSoundLevel_19CA0(uint8_t option);
int sub_582B0(__int16 a1, __int16 a2);
int sub_582F0(int a1, __int16 a2);
bool sub_6EA90(int a1, int a2);
