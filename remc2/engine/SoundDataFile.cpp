#include "SoundDataFile.h"

SoundDataFile::SoundDataFile(std::string soundPath, int32_t sampleOffset) : m_soundPath{ soundPath }, m_sampleOffset { sampleOffset }
{
	FILE* ptrFile = DataFileIO::CreateOrOpenFile(soundPath.c_str(), 512);

	LoadData(ptrFile);
};

SoundDataFile::~SoundDataFile()
{
	for (int i = 0; i < m_Samples.size(); i++)
	{
		delete m_Samples[i].data_44;
	}
	m_Samples.clear();
}

bool SoundDataFile::LoadData(FILE* ptrFile)
{
	if (ptrFile == nullptr)
		return false;

	DataFileIO::Seek(ptrFile, 0, 2);
	m_fileSize = myftell(ptrFile);
	DataFileIO::Seek(ptrFile, m_fileSize - 4, 0);
	DataFileIO::Read(ptrFile, (uint8_t*)&m_bankStartIdex, 4);

	LoadSamples(ptrFile, 0);

	DataFileIO::Close(ptrFile);

	return true;
};

bool SoundDataFile::LoadSamples(FILE* ptrFile, int32_t startOffset, int32_t samplePaddingBytes)
{
	int MAX_SAMPLES = 64;
	while (MAX_SAMPLES)
	{
		startOffset = LoadSample(ptrFile, startOffset);
		if (startOffset < 0)
			break;

		startOffset += samplePaddingBytes;
		MAX_SAMPLES--;
	}

	return true;
};

int64_t SoundDataFile::LoadSample(FILE* ptrFile, int32_t startOffset)
{
	char fileType[] = { 'R','I','F','F' };
	wav_t wavFile;
	DataFileIO::Seek(ptrFile, startOffset, 0);
	DataFileIO::Read(ptrFile, (uint8_t*)&wavFile, WAVE_HEADER_SIZE_BYTES);

	wavFile.data_44 = new uint8_t[wavFile.dataSizeBytes_40];

	if (!std::equal(std::begin(wavFile.isRiff_0), std::end(wavFile.isRiff_0), std::begin(fileType)) || wavFile.dataSizeBytes_40 < 1)
		return -1;

	DataFileIO::Seek(ptrFile, startOffset + WAVE_HEADER_SIZE_BYTES, 0);
	DataFileIO::Read(ptrFile, wavFile.data_44, wavFile.dataSizeBytes_40);

	m_Samples.push_back(wavFile);

	return startOffset + WAVE_HEADER_SIZE_BYTES + wavFile.dataSizeBytes_40;
};