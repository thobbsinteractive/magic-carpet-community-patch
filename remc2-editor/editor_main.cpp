using namespace std;

#include <stdio.h>
#include <cstdint>
#include <assert.h>
#include <sstream>
#include <stddef.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

#include "png.h"
#pragma comment(lib, "zlib.lib") // must be before libpng!
#ifndef _WIN64
#pragma comment(lib, "libpng15.lib") // must be after zlib!
#else
#endif

#ifdef _MSC_VER
	#include "SDL.h"
#else
    #include "SDL2/SDL.h"
#endif
#include "editor.h"

int main(int argc, char* argv[])
{	
	spdlog::level::level_enum level = spdlog::level::info;



#ifdef _DEBUG
	level = GetLoggingLevelFromString("Debug");
#else
	level = GetLoggingLevelFromString(loggingLevel.c_str());
#endif
	InitializeLogging(level);

	support_begin();
	//(*filearray_2aa18c[filearrayindex_BUILD00DATTAB].posistruct)[0x11].data

    editor_run();
	//VGA_close();
    return 0;
}

