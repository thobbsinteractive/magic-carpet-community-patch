#pragma once

#ifndef SOUND_DATE_FILE
#define SOUND_DATE_FILE

#include <string>
#include <array>
#include <thread>
#include "defs.h"
#include "../utilities/DataFileIO.h"

class SoundDataFile
{
private:
	std::string m_soundPath;
	int32_t m_bankStartIdex = 0;

public:
	SoundDataFile(std::string soundPath);
	bool LoadData(FILE* ptrFile);
};

#endif //SOUND_DATE_FILE