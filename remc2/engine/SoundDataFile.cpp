#include "SoundDataFile.h"

SoundDataFile::SoundDataFile(std::string soundPath) : m_soundPath{ soundPath }
{
	FILE* ptrFile = DataFileIO::CreateOrOpenFile(soundPath.c_str(), 512);

	LoadData(ptrFile);
};

bool SoundDataFile::LoadData(FILE* ptrFile)
{
	if (ptrFile == nullptr)
		return false;

	DataFileIO::Seek(ptrFile, 0, 2);
	long sizeOfFile = myftell(ptrFile);
	DataFileIO::Seek(ptrFile, sizeOfFile - 4, 0);
	DataFileIO::Read(ptrFile, (uint8_t*)&m_bankStartIdex, 4);
	DataFileIO::Close(ptrFile);
};