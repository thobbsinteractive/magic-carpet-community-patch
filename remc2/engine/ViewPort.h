#pragma once

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <cstdint>

struct ViewPort
{
	uint16_t PreHeight_EA3C0 = 0;
	uint16_t PreWidth_EA3C4 = 0;
	//uint16_t x_DWORD_EA3C8 = 0;
	uint16_t PosY_EA3CC = 0;
	uint16_t PosX_EA3D0 = 0;

	uint16_t Width_DE564 = 0;
	uint16_t Height_DE568 = 0;


	ViewPort()
	{
		PosX_EA3D0 = 0;
		PosY_EA3CC = 0;
		Width_DE564 = 0;
		Height_DE568 = 0;

		PreHeight_EA3C0 = 0;
		PreWidth_EA3C4 = 0;
	};

	ViewPort(const ViewPort &v)
	{
		PosX_EA3D0 = v.PosX_EA3D0;
		PosY_EA3CC = v.PosY_EA3CC;
		Width_DE564 = v.Width_DE564;
		Height_DE568 = v.Height_DE568;

		PreHeight_EA3C0 = v.PreHeight_EA3C0;
		PreWidth_EA3C4 = v.PreWidth_EA3C4;
	};

	ViewPort(uint16_t viewPortPosX, uint16_t viewPortPosY, uint16_t viewPortWidth, uint16_t viewPortHeight)
	{
		PosX_EA3D0 = viewPortPosX;
		PosY_EA3CC = viewPortPosY;
		Width_DE564 = viewPortWidth;
		Height_DE568 = viewPortHeight;
	};

	ViewPort(uint16_t viewPortPosX, uint16_t viewPortPosY, uint16_t viewPortWidth, uint16_t viewPortHeight, uint16_t viewPortPreWidth, uint16_t viewPortPreHeight)
	{
		PosX_EA3D0 = viewPortPosX;
		PosY_EA3CC = viewPortPosY;
		Width_DE564 = viewPortWidth;
		Height_DE568 = viewPortHeight;

		PreWidth_EA3C4 = viewPortPreWidth;
		PreHeight_EA3C0 = viewPortPreHeight;		
	};
};

#endif //VIEWPORT_H