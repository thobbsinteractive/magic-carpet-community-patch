#pragma once

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <cstdint>

struct ViewPort
{
	uint16_t PosX_EA3D0 = 0;
	uint16_t PosY_EA3CC = 0;
	uint16_t Width_DE564 = 0;
	uint16_t Height_DE568 = 0;

	ViewPort()
	{
		PosX_EA3D0 = 0;
		PosY_EA3CC = 0;
		Width_DE564 = 0;
		Height_DE568 = 0;
	};

	ViewPort(const ViewPort &v)
	{
		PosX_EA3D0 = v.PosX_EA3D0;
		PosY_EA3CC = v.PosY_EA3CC;
		Width_DE564 = v.Width_DE564;
		Height_DE568 = v.Height_DE568;
	};

	ViewPort(uint16_t viewPortPosX, uint16_t viewPortPosY, uint16_t viewPortWidth, uint16_t viewPortHeight)
	{
		PosX_EA3D0 = viewPortPosX;
		PosY_EA3CC = viewPortPosY;
		Width_DE564 = viewPortWidth;
		Height_DE568 = viewPortHeight;
	};
};

#endif //VIEWPORT_H