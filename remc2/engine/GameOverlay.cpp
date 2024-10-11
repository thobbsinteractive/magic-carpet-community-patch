#include "GameOverlay.h"

void GameOverlay::DrawTransparentBitmap_2DE80(int16_t posX, int16_t posY, posistruct_t a3, uint8_t scale)//20ee80
{
	int32_t startOffsetX; // eax
	uint8_t* v5; // edi
	int16_t posHeight; // bx
	uint8_t* ptrScreenBuffer;
	uint8_t* ptrBitmapData = nullptr; // edx
	uint8_t* ptrBitmapPixel = nullptr; // esi
	int32_t posWidth; // ecx
	int v15; // [esp+0h] [ebp-Ch]
	int32_t width; // [esp+0h] [ebp-Ch]
	uint8_t* ptrScreenBufferLineStart; // [esp+4h] [ebp-8h]
	uint8_t* i; // [esp+8h] [ebp-4h]

	if (x_WORD_180660_VGA_type_resolution == 1)
	{
		posHeight = a3.height_5 / 2;
		startOffsetX = posY / 2 * screenWidth_18062C + posX / 2;
		v5 = (startOffsetX + pdwScreenBuffer_351628);
		ptrBitmapData = a3.data;
		for (i = startOffsetX + pdwScreenBuffer_351628; posHeight; ptrBitmapData += v15)
		{
			while (1)
			{
				while (1)
				{
					LOBYTE(startOffsetX) = *ptrBitmapData++;
					if ((x_BYTE)startOffsetX)
						break;
					posHeight--;
					i += screenWidth_18062C;
					v5 = i;
					if (!posHeight)
						return;
				}
				if ((startOffsetX & 0x80u) == 0)
					break;
				v5 -= (char)startOffsetX;
				if (!posHeight)
					return;
			}
			startOffsetX = (char)startOffsetX;//20ef1f
			ptrBitmapPixel = ptrBitmapData;
			posWidth = startOffsetX;
			v15 = (char)startOffsetX;
			HIWORD(startOffsetX) = 0;
			do
			{
				LOBYTE(startOffsetX) = *ptrBitmapPixel++;
				HIBYTE(startOffsetX) = *v5;
				LOBYTE(startOffsetX) = x_BYTE_F6EE0_tablesx[0x4000 + startOffsetX];
				*v5++ = startOffsetX;
				posWidth--;
			} while (posWidth);
		}
	}
	else
	{
		if (a3.height_5)
		{
			startOffsetX = posX + screenWidth_18062C * posY;
			posHeight = a3.height_5;

			ptrScreenBuffer = (startOffsetX + pdwScreenBuffer_351628);
			ptrScreenBufferLineStart = (startOffsetX + pdwScreenBuffer_351628);
			ptrBitmapData = a3.data;
			int lineStartBytes = 0;
			int countBytes = 0;
			int scaledLinesDrawn = 0;

			do
			{
				while (1)
				{
					while (1)
					{
						LOBYTE(startOffsetX) = *ptrBitmapData++;
						countBytes++;

						//If it has value
						if ((x_BYTE)startOffsetX)
							break;

						//Move row
						if (scaledLinesDrawn < scale - 1)
						{
							int lineLengthBytes = countBytes - lineStartBytes;
							ptrBitmapData -= lineLengthBytes;
							countBytes -= lineLengthBytes;
							scaledLinesDrawn++;
						}
						else
						{
							posHeight--;
							scaledLinesDrawn = 0;
							lineStartBytes = countBytes;
						}

						ptrScreenBufferLineStart += screenWidth_18062C;
						ptrScreenBuffer = ptrScreenBufferLineStart;
						if (!posHeight)
							return;
					}

					//Is width byte
					if ((startOffsetX & 0x80u) == 0)
					{
						//Start Drawing
						break;
					}
					//Is a change of start coordinate
					int offset = (char)startOffsetX;
					ptrScreenBuffer -= offset * scale;
					if (!posHeight)
						return;
				}
				posWidth = LOBYTE(startOffsetX);
				width = LOBYTE(startOffsetX);
				ptrBitmapPixel = ptrBitmapData;
				HIWORD(startOffsetX) = 0;
				//Draw line
				do
				{
					for (int s = 0; s < scale; s++)
					{
						LOBYTE(startOffsetX) = *ptrBitmapPixel;
						HIBYTE(startOffsetX) = *ptrScreenBuffer;
						LOBYTE(startOffsetX) = x_BYTE_F6EE0_tablesx[0x4000 + startOffsetX];
						*ptrScreenBuffer++ = startOffsetX;
					}
					ptrBitmapPixel++;
					countBytes++;
					posWidth--;
				} while (posWidth);
				ptrBitmapData += width;
			} while (posHeight);
		}
	}
};