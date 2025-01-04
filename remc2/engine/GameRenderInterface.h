#pragma once

#ifndef GAME_RENDER_INTERFACE
#define GAME_RENDER_INTERFACE

#include <cstdint>
#include "engine_support.h"
#include "ViewPort.h"

class GameRenderInterface 
{
public:
	virtual ~GameRenderInterface() {}
	virtual void DrawWorld_411A0(int posX, int posY, int16_t yaw, int16_t posZ, int16_t pitch, int16_t roll, int16_t fov) = 0;
};

extern GameRenderInterface* m_ptrGameRender;
extern uint8_t loc_A0000_vga_buffer[307200];
extern TColor x_DWORD_EA3B8x[256];
extern int16_t x_WORD_180662_graphics_handle;
extern bitmap_pos_struct2_t* x_DWORD_D4188;
extern bitmap_pos_struct2_t* x_DWORD_D418C;
extern bitmap_pos_struct2_t* x_DWORD_D4190;


void sub_A0D50_set_viewport(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height);


#endif //GAME_RENDER_INTERFACE