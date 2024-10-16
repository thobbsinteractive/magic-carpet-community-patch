#pragma once

#ifndef GAME_BITMAP
#define GAME_BITMAP

#include "basic.h"

class GameBitmap
{
public:
	static void DrawBitmap(uint8_t* ptrBitmapData, uint8_t* ptrScreenBuffer, uint8_t height, uint8_t scale = 1);
	static void DrawBitmap(uint8_t* ptrBitmapData, uint8_t* ptrScreenBuffer, uint32_t width, uint16_t height, uint8_t v134);
	static void DrawTransparentBitmap_2DE80(int16_t posX, int16_t posY, posistruct_t a3, uint8_t scale = 1);
};

#endif //GAME_BITMAP