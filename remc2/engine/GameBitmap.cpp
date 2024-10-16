#include "GameBitmap.h"

void GameBitmap::DrawBitmap(uint8_t* ptrBitmapData, uint8_t* ptrScreenBuffer, uint8_t height, uint8_t scale)
{
	int8_t width = 0;
	int8_t posWidth = 0;
	int8_t startOffsetX = -1;
	uint8_t pixel = 0;
	uint8_t* ptrScreenBufferLineStart = ptrScreenBuffer;

	int scaledLinesDrawn = 0;

	do
	{
		while (1)
		{
			while (1)
			{
				startOffsetX = *ptrBitmapData++;

				//Is width byte
				if ((startOffsetX & 0x80u) == 0)
				{
					//Start Drawing
					break;
				}

				//Get start location using Offset byte
				int offset = (char)startOffsetX;
				uint8_t* ptrCurrentScreenLineStart = ptrScreenBuffer - (offset * scale);
				width = *ptrBitmapData;
				posWidth = *ptrBitmapData;
				uint8_t* ptrCurrentBitmapLineStart = (ptrBitmapData + 1);

				if (width < 1)
					break;

				if (scale > 1)
				{
					do
					{
						pixel = *ptrCurrentBitmapLineStart++;
						for (int s = 0; s < scale; s++)
						{
							*ptrCurrentScreenLineStart++ = pixel;
						}
						posWidth--;
					} while (posWidth);
					ptrBitmapData = ptrCurrentBitmapLineStart;
					ptrScreenBuffer = ptrCurrentScreenLineStart;
				}
				else
				{
					qmemcpy(ptrCurrentScreenLineStart, ptrCurrentBitmapLineStart, width);
					ptrBitmapData = ptrCurrentBitmapLineStart + width;
					ptrScreenBuffer = ptrCurrentScreenLineStart + width;
				}
			}

			//If null byte move to next row...
			if (startOffsetX < 1)
				break;

			//Draw line
			width = startOffsetX;
			posWidth = startOffsetX;

			if (scale > 1)
			{
				do
				{
					pixel = *ptrBitmapData++;
					for (int s = 0; s < scale; s++)
					{
						*ptrScreenBuffer++ = pixel;
					}
					posWidth--;
				} while (posWidth);
			}
			else
			{
				qmemcpy(ptrScreenBuffer, ptrBitmapData, width);
				ptrBitmapData += width;
				ptrScreenBuffer += width;
			}
		}
		ptrScreenBufferLineStart += screenWidth_18062C;
		ptrScreenBuffer = ptrScreenBufferLineStart;
		height--;
	} while (height);
};

void GameBitmap::DrawBitmap(uint8_t* ptrBitmapData, uint8_t* ptrScreenBuffer, uint32_t width, uint16_t height, uint8_t v134)
{
	uint8_t pixel;
	int32_t startOffsetX;
	int32_t posWidth;
	uint8_t* ptrScreenBufferLineStart = ptrScreenBuffer;

	do
	{
		while (1)
		{
			while (1)
			{
				startOffsetX = *ptrBitmapData++;

				//Is width byte
				if ((startOffsetX & 0x80u) == 0)
				{
					//Start Drawing
					break;
				}
				ptrScreenBuffer += startOffsetX;
				width = width - startOffsetX;
			}
			if (!startOffsetX)
				break;
			posWidth = startOffsetX;

			//Draw Line
			do
			{
				pixel = *ptrBitmapData++;
				width = width + 1;
				if ((width & 0x80u) == 0)
					*ptrScreenBuffer = pixel;
				--ptrScreenBuffer;
				--posWidth;
			} while (posWidth);
		}
		ptrScreenBufferLineStart += screenWidth_18062C;
		ptrScreenBuffer = ptrScreenBufferLineStart;
		width = __PAIR__(height, v134) - 256;
	} while (height);
};

void GameBitmap::DrawTransparentBitmap_2DE80(int16_t posX, int16_t posY, posistruct_t a3, uint8_t scale)//20ee80
{
	int32_t startOffsetX; // eax
	int16_t posHeight; // bx
	uint8_t* ptrScreenBuffer;
	uint8_t* ptrBitmapData = nullptr; // edx
	uint8_t* ptrBitmapPixel = nullptr; // esi
	int32_t posWidth; // ecx
	int v15; // [esp+0h] [ebp-Ch]
	int32_t width; // [esp+0h] [ebp-Ch]
	uint8_t* ptrScreenBufferLineStart; // [esp+4h] [ebp-8h]

	if (x_WORD_180660_VGA_type_resolution == 1)
	{
		posHeight = a3.height_5 / 2;
		startOffsetX = posY / 2 * screenWidth_18062C + posX / 2;
		ptrScreenBuffer = (startOffsetX + pdwScreenBuffer_351628);
		ptrBitmapData = a3.data;
		for (ptrScreenBufferLineStart = startOffsetX + pdwScreenBuffer_351628; posHeight; ptrBitmapData += v15)
		{
			while (1)
			{
				while (1)
				{
					LOBYTE(startOffsetX) = *ptrBitmapData++;
					if ((x_BYTE)startOffsetX)
						break;
					posHeight--;
					ptrScreenBufferLineStart += screenWidth_18062C;
					ptrScreenBuffer = ptrScreenBufferLineStart;
					if (!posHeight)
						return;
				}
				if ((startOffsetX & 0x80u) == 0)
					break;
				ptrScreenBuffer -= (char)startOffsetX;
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
				HIBYTE(startOffsetX) = *ptrScreenBuffer;
				LOBYTE(startOffsetX) = x_BYTE_F6EE0_tablesx[0x4000 + startOffsetX];
				*ptrScreenBuffer++ = startOffsetX;
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