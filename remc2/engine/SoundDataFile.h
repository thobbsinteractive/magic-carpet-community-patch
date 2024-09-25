#pragma once

#ifndef SOUND_DATE_FILE
#define SOUND_DATE_FILE

#include <string>
#include <array>
#include <thread>
#include "defs.h"
#include "../utilities/Wave.h"
#include "../utilities/DataFileIO.h"

class SoundDataFile
{
private:
	std::string m_soundPath;
	int64_t m_fileSize = 0;
	int32_t m_bankStartIdex = 0;
	int32_t m_sampleOffset = 90;
	std::vector<wav_t> m_Samples;

public:
	SoundDataFile(std::string soundPath, int32_t sampleOffset = 90);
	~SoundDataFile();
	bool LoadData(FILE* ptrFile);
	bool LoadSamples(FILE* ptrFile, int32_t startOffset, int32_t samplePaddingBytes = 4);
	int64_t LoadSample(FILE* ptrFile, int32_t startOffset);
};

#endif //SOUND_DATE_FILE