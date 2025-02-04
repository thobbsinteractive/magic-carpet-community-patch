#include <cstdint>
#include <gtest/gtest.h>
#include "../../remc2/engine/GameRenderHD.h"

TEST(GameRenderHD, CalculateRotationTranslationX)
{
	//Arrange
	str_F2C20ar.cos_0x11 = 65536;
	Str_E9C38_smalltit[0].pnt1_16 = 33637;
	str_F2C20ar.sin_0x0d = 0;
	Str_E9C38_smalltit[0].pnt2_20 = -9735;
	str_F2C20ar.dword0x24 = 960;

	//Run original code
	int32_t pnt1_16o = ((str_F2C20ar.cos_0x11 * Str_E9C38_smalltit[0].pnt1_16 - str_F2C20ar.sin_0x0d * Str_E9C38_smalltit[0].pnt2_20) >> 16) + str_F2C20ar.dword0x24;

	//Run current code
	int32_t pnt1_16n = GameRenderHD::CalculateRotationTranslationX(str_F2C20ar.cos_0x11, Str_E9C38_smalltit[0].pnt1_16, str_F2C20ar.sin_0x0d, Str_E9C38_smalltit[0].pnt2_20);

	//Check results match
	ASSERT_EQ(pnt1_16o, -30939);
	ASSERT_EQ(pnt1_16n, 34597);
}

TEST(GameRenderHD, SumByte1WithByte2)
{
	//Arrange
	int byte1 = 2;

	//Run current code
	byte1 = GameRenderHD::SumByte1WithByte2(byte1, -2231, 0);
	ASSERT_EQ(byte1, 65282);

	byte1 = 8759;
	byte1 = GameRenderHD::SumByte1WithByte2(byte1, 53, 0);
	ASSERT_EQ(byte1, 8759);

	byte1 = 258;
	byte1 = GameRenderHD::SumByte1WithByte2(byte1, -2231, 1);
	ASSERT_EQ(byte1, 258);
}

TEST(GameRenderHD, RenderCrashTest1)
{
	//Arrange
	unsigned __int8 v180 = 0;
	int v1124 = 1137;
	int v383 = -1267360;

	//Run current code
	v180 = __CFADD__((x_WORD)v1124, (x_WORD)v383);

	ASSERT_EQ(v180, 0);

	LOWORD(v383) = v1124 + v383;

	ASSERT_EQ(v383, -1266223);
}

TEST(GameRenderHD, RenderCrashTest2)
{
	//Arrange
	unsigned __int8 v180 = 0;
	int v1124 = 1137;
	int v383 = 175154415;
	int v376 = 26;
	auto v389 = new uint8_t[65536];
	unsigned int v375 = 5681;
	uint v1167 = 4118544384;
	uint v1135 = -2692;

	//Run current code
	v180 = __CFADD__((x_WORD)v1124, (x_WORD)v383);

	ASSERT_EQ(v180, 0);

	LOWORD(v383) = v1124 + v383;

	ASSERT_EQ(v383, 175155552);

	LOBYTE(v375) = *(x_BYTE*)(v376 + v389);

	//ASSERT_EQ(v375, 5681);

	LOBYTE(v376) = BYTE2(v1124) + v180 + v376;

	ASSERT_EQ(v376, 26);

	v180 = __CFADD__((uint64)v1167, (int64)v383);

	ASSERT_EQ(v180, 0);

	v383 += v1167;

	ASSERT_EQ(v383, -1267360);
	ASSERT_EQ(v1167, 4118544384);

	v376 = GameRenderHD::SumByte1WithByte2(v376, v1135, v180);

	ASSERT_EQ(v376, 65306);
}