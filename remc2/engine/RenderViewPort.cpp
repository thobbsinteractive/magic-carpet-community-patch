#include "RenderViewPort.h"
#include "defs.h"

RenderViewPort::RenderViewPort(uint16_t viewPortPosX, uint16_t viewPortPosY, uint16_t viewPortWidth, uint16_t viewPortHeight, uint16_t screenWidth, uint16_t screenHeight, uint8_t* screenBuffer)
{
	m_ptrScreenBufferStart = screenBuffer;
	SetRenderViewPortSize_BCD45(viewPortPosX, viewPortPosY, viewPortWidth, viewPortHeight, screenWidth, screenHeight);
};

void RenderViewPort::SetRenderViewPortSize_BCD45(uint16_t viewPortPosX, uint16_t viewPortPosY, uint16_t viewPortWidth, uint16_t viewPortHeight, uint16_t screenWidth, uint16_t screenHeight)
{
	m_iScreenWidth = screenWidth;
	PosX_EA3D0 = viewPortPosX;
	PosY_EA3CC = viewPortPosY;
	PreWidth_EA3C4 = viewPortWidth;
	PreHeight_EA3C0 = viewPortHeight;
	Width_DE564 = viewPortWidth;
	Height_DE568 = viewPortHeight;

	if (viewPortWidth > screenWidth)
	{
		Width_DE564 = screenWidth;
	}

	if (viewPortHeight > screenHeight)
	{
		Height_DE568 = screenHeight;
	}

	if (viewPortPosX > screenWidth)
	{
		PosX_EA3D0 = screenWidth - 1;
	}

	if (viewPortPosY > screenHeight)
	{
		PosY_EA3CC = screenHeight - 1;
	}

	int32_t ptrScreenRenderBufferStart = PosX_EA3D0 + screenWidth * PosY_EA3CC;
	SetRenderViewPortSize_BCD45(ptrScreenRenderBufferStart + m_ptrScreenBufferStart, screenWidth, Width_DE564, Height_DE568);
}

void RenderViewPort::SetRenderViewPortSize_BCD45(uint8_t* ptrScreenBufferStart, uint16_t screenWidth, uint16_t viewPortWidth, uint16_t viewPortHeight)
{
	if (screenWidth)
	{
		m_iScreenWidth = screenWidth;
	}

	if (ptrScreenBufferStart)
	{
		m_ptrScreenBufferStart = ptrScreenBufferStart;
		m_ptrScreenBufferAltStart = ptrScreenBufferStart - m_iScreenWidth;
	}

	if (viewPortWidth)
	{
		Width_DE564 = viewPortWidth;
	}

	if (viewPortHeight)
	{
		Height_DE568 = viewPortHeight;
	}
}