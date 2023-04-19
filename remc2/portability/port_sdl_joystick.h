#pragma once
#ifndef PORT_SDL_JOYSTICK_H
#define PORT_SDL_JOYSTICK_H

#include <cstdint>
#include <stdio.h>
#include <assert.h>
#include <sstream>
#include <stddef.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

#ifdef _MSC_VER
	#include "SDL.h"
#else
    #include "SDL2/SDL.h"
#endif

#include "port_sdl_sound.h"
#include "port_filesystem.h"

#define  SCENE_PREAMBLE_MENU  0x1
#define         SCENE_FLIGHT  0x2
#define    SCENE_FLIGHT_MENU  0x3

///< gamepad_event_t flags
#define        GP_BTN_RELEASED  0x40
#define         GP_BTN_PRESSED  0x80


struct gamepad_state {
	int32_t x;
	int32_t y;
	int32_t rest_x;
	int32_t rest_y;
	int32_t max_x;
	int32_t max_y;
	uint8_t dead_zone_announced;   ///< slow infinite spin mitigation when joystick is in the resting position while in the flying window
	uint8_t initialized;
	uint8_t scene_id;
	uint8_t nav_mode;
};
typedef struct gamepad_state gamepad_state_t;

struct gamepad_event {
	int16_t axis_yaw;
	int16_t axis_pitch;
	int16_t axis_long;
	int16_t axis_trans;
	int16_t axis_nav_ns;
	int16_t axis_nav_ew;
	uint8_t hat_nav;
	uint8_t hat_mov;
	uint64_t btn_released;  ///< bitwise OR of every released button
	uint64_t btn_pressed;   ///< bitwise OR of every pressed button
	uint8_t flag;           ///< bitwise OR of every parameter that was updated
};
typedef struct gamepad_event gamepad_event_t;

void set_scene(const uint8_t scene_id);
void joystick_set_env(const int32_t x, const int32_t y);
void gamepad_sdl_init(void);
void gamepad_sdl_close(void);
void gamepad_init(const int gameResWidth, const int gameResHeight);
void gamepad_poll_data(gamepad_event_t *gpe);

extern gamepad_state_t gps;

#endif //PORT_SDL_JOYSTICK
