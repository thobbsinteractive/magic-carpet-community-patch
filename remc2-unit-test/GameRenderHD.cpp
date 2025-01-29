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