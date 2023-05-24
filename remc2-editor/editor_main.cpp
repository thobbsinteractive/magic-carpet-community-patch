using namespace std;

#include <stdio.h>
#include <cstdint>
#include <assert.h>
#include <sstream>
#include <stddef.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

#include "png.h"

#ifdef _MSC_VER
	#include "SDL.h"
#else
    #include "SDL2/SDL.h"
#endif
#include "editor.h"

int main(int argc, char* argv[])
{	
	spdlog::level::level_enum level = spdlog::level::info;
	std::string gameFolder;
	std::string cdFolder;
	std::vector<std::string> params;
	params.clear();
	bool showHelp = false;

	for (int i = 1; i < argc; ++i) {
		params.emplace_back(argv[i]);
}
	for (auto p = params.cbegin(); p != params.cend(); ++p) {
		const auto param = *p;
		
		if ((param == "-g") || (param == "--game-folder"))
		{
			gameFolder = *(++p);
		}
		if ((param == "-c") || (param == "--cd-folder"))
		{
			cdFolder = *(++p);
		}
		else if ((param == "-h") || (param == "--help")) {
			showHelp = true;
		}
	}

	if (showHelp)
	{
		printf("-g --game-folder: (Optional) Folder Location of MC2 Game Data. Defaults to ./GAME/NETHERW. \n");
		printf("-c --cd-folder: (Optional) Folder Location of MC2 CD Data.  Defaults to ./CD_FILES. \n");
		return -1;
	}

#ifdef _DEBUG
	level = GetLoggingLevelFromString("Debug");
#else
	level = GetLoggingLevelFromString(loggingLevel.c_str());
#endif
	InitializeLogging(level);

	support_begin();

    editor_run(gameFolder, cdFolder);

    return 0;
}

