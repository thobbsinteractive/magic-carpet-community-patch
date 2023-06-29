using namespace std;

#include <stdio.h>
#include <cstdint>
#include <assert.h>
#include <sstream>
#include <stddef.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

#include "png.h"

#include "SDL2/SDL.h"

#include "editor.h"

int main(int argc, char* argv[])
{	
	int exitCode = 0;
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
		if ((param == "-l") || (param == "--log-level"))
		{
			loggingLevel = *(++p);
		}
		if ((param == "-h") || (param == "--help")) {
			showHelp = true;
		}
	}

	if (showHelp)
	{
		printf("-g --game-folder: (Optional) Folder Location of MC2 Game Data. Defaults to ./NETHERW. \n");
		printf("-c --cd-folder: (Optional) Folder Location of MC2 CD Data.  Defaults to ./CD_FILES. \n");
		printf("-l --log-level: (Optional) Logging Level E.g. Debug, Trace or Info.  Defaults to Info \n");
		return -1;
	}

#ifdef _DEBUG
	level = GetLoggingLevelFromString("Debug");
#else
	level = GetLoggingLevelFromString(loggingLevel.c_str());
#endif

	try
	{
		InitializeLogging(level, "log-editor.txt");
		support_begin();
		editor_run(gameFolder, cdFolder);
	}
	catch (const std::exception& e)
	{
		Logger->critical("Critial Error: {}", e.what());
		exitCode = -1;
	}
	Logger->info("Exited Game");

    return 0;
}

