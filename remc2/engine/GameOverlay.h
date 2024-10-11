#pragma once

#ifndef GAME_OVERLAY
#define GAME_OVERLAY

#include "basic.h"

class GameOverlay
{
public:
	static void DrawTransparentBitmap_2DE80(int16_t posX, int16_t posY, posistruct_t a3, uint8_t scale = 1);
};

#endif //GAME_OVERLAY