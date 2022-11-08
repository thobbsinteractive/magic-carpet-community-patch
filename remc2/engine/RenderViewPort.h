#pragma once

#ifndef RENDER_VIEWPORT_H
#define RENDER_VIEWPORT_H

#include "Rectangle.h"
#include "globals.h"

class RenderViewPort : public Rectangle
{
private:
	void SetRenderViewPortSize_BCD45(uint16_t viewPortPosX, uint16_t viewPortPosY, uint16_t viewPortWidth, uint16_t viewPortHeight, uint16_t screenWidth, uint16_t screenHeight);
	void SetRenderViewPortSize_BCD45(uint8_t* ptrScreenBufferStart, uint16_t screenWidth, uint16_t viewPortWidth, uint16_t viewPortHeight);
public:
	uint16_t PreWidth_EA3C4 = 0;
	uint16_t PreHeight_EA3C0 = 0;
	int m_iScreenWidth;
	uint8_t* m_ptrScreenBufferStart;
	uint8_t* m_ptrScreenBufferAltStart;

	RenderViewPort(uint16_t viewPortPosX, uint16_t viewPortPosY, uint16_t viewPortWidth, uint16_t viewPortHeight, uint16_t screenWidth, uint16_t screenHeight, uint8_t* screenBuffer);
};

#endif //RENDER_VIEWPORT_H