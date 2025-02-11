#pragma once
#ifndef PORT_FILESYSTEM_H
#define PORT_FILESYSTEM_H

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <string>
#include "bitmap_pos_struct.h"
#include "fcaseopen.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef _MSC_VER
	#include <windows.h>
	#include <direct.h>
	#include <io.h>
	#include "dirent-x.h"
#else
	#include "dirent.h"
	extern "C" {
    	#include "findfirst.h"
	}
	#include <limits.h>

	#define MAX_PATH PATH_MAX
	#define _chdir chdir
#endif

//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
// 
//#define DEBUG_PRINT_DEBUG_TO_SCREEN

extern char gameFolder[512];
extern char cdFolder[512];
extern char bigGraphicsFolder[512];
extern char forceRender[512];
extern spdlog::logger* Logger;

const char* GetStringFromLoggingLevel(spdlog::level::level_enum level);
spdlog::level::level_enum GetLoggingLevelFromString(const char* levelStr);
void InitializeLogging(spdlog::level::level_enum level);
void InitializeLogging(spdlog::level::level_enum level, const char* logFileName);
long my_findfirst(char* path, _finddata_t* c_file);
long my_findnext(long hFile, _finddata_t* c_file);
void my_findclose(long hFile);
bool file_exists(const char * filename);
FILE* mycreate(const char* path, uint32_t flags);
int32_t myaccess(const char* path, uint32_t flags);
int32_t mymkdir(const char* path);

FILE* myopen(const char* path, int pmode, uint32_t flags);
int myclose(FILE* descriptor);
int32_t mylseek(FILE* filedesc, x_DWORD position, char type);
int32_t myfseek(FILE* filedesc, x_DWORD position, char type);

void AdvReadfile(const char* path, uint8_t* buffer);
long ReadGraphicsfile(const char* path, uint8_t* buffer,long size=-1);
bool ExistGraphicsfile(const char* path);

long myftell(FILE* decriptor);

int DirExists(const char* path);

FILE* myopent(char* path, char* type);

typedef struct {
	int number;
	char dir[256][512];
} dirsstruct;

dirsstruct getListDir(char* dirname);
//dirsstruct getListDirFix(char* dirname);
void FixDir(char* outdirname, char* indirname);

int dos_getdrive(int* a);

std::string get_exe_path();

#ifdef _MSC_VER
uint64_t dos_getdiskfree(int16_t a1, int16_t a2, uint8_t a, short* b);
#endif

std::string GetSubDirectoryPath(const char* subDirectory);

std::string GetSubDirectoryPath(const char* gamepath, const char* subDirectory);

std::string GetSubDirectoryFilePath(const char* subDirectory, const char* fileName);

std::string GetSubDirectoryFile(const char* gamepath, const char* subDirectory, const char* fileName);

std::string GetSaveGameFile(const char* gamepath, int16_t index);

int GetDirectory(char* directory, const char* filePath);

#endif //PORT_FILESYSTEM
