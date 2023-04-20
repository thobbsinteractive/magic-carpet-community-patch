#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _MSC_VER
    #include <direct.h>  
    #include <io.h>  
    #include <windows.h>
    #include "../portability/dirent-x.h"
#else
    #include "dirent.h"
#endif

#include "../portability/port_time.h"
#include "../portability/port_filesystem.h"
#include "../portability/port_sdl_sound.h"
#include "defs.h"

#include "INIReader.h"
#include "ini.h"



#ifndef READ_CONFIG
#define READ_CONFIG

bool readini();
extern int config_skip_screen;
extern int texturepixels;
extern int maxGameFps;
extern int fmvFps;
extern int menuFps;
extern std::string loggingLevel;
extern int displayIndex;
extern int windowResWidth;
extern int windowResHeight;
extern int gameResWidth;
extern int gameResHeight;
extern bool maintainAspectRatio;
extern bool forceWindow;
extern bool bigTextures;
extern bool bigSprites;
extern bool sky;
extern bool reflections;
extern bool dynamicLighting;
extern bool openGLRender;
extern bool multiThreadedRender;
extern int numberOfRenderThreads;
extern bool assignToSpecificCores;

#define   GAMEPAD_ITEM_DISABLED  0x0
#define    GAMEPAD_ITEM_ENABLED  0x1
#define   GAMEPAD_AXIS_INVERTED  0x2

struct gamepad_config {
	uint16_t axis_yaw;
	uint16_t axis_pitch;
	uint16_t axis_long;
	uint16_t axis_trans;
	uint16_t axis_nav_ns;
	uint16_t axis_nav_ew;
	uint16_t axis_fire_R;
	uint16_t axis_fire_L;
	uint8_t axis_yaw_conf;
	uint8_t axis_pitch_conf;
	uint8_t axis_long_conf;
	uint8_t axis_trans_conf;
	uint8_t axis_nav_ns_conf;
	uint8_t axis_nav_ew_conf;
	uint8_t axis_fire_R_conf;
	uint8_t axis_fire_L_conf;
	uint16_t axis_dead_zone;
	uint16_t hat_nav;
	uint16_t hat_mov;
	uint8_t hat_mov_conf;
	uint8_t hat_nav_conf;
	uint16_t button_spell;
	uint16_t button_minimap;
	uint16_t button_fire_R;
	uint16_t button_fire_L;
	uint16_t button_fwd;
	uint16_t button_back;
};

typedef struct gamepad_config gamepad_config_t;
extern gamepad_config_t gpc;

#endif //READ_CONFIG
