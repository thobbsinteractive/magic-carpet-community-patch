#pragma once
#ifndef READCONFIG
#define READCONFIG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <filesystem>
#include <cstdlib>

#ifdef _MSC_VER
    #include <direct.h>  
    #include <io.h>  
    #include <windows.h>
#else
    #include "dirent.h"
#endif

#include "../remc2/engine/CommandLineParser.h"
#include "../remc2/portability/port_filesystem.h"
#include "INIReader.h"
#include "ini.h"

class ReadConfig
{
private:
	std::string FindIniFile();

public:
	bool ReadIni();
};

#endif //READCONFIG
