#pragma once

#ifndef GAME_RENDER_HD
#define GAME_RENDER_HD

#include "GameRenderInterface.h"

#include <array>
#include <thread>

#include "../utilities/Maths.h"
#include "../utilities/BitmapIO.h"
#include "../portability/bitmap_pos_struct.h"
#include "../utilities/SafeQueue.h"
#include "Terrain.h"
#include "Type_F2C20ar.h"
#include "Type_E9C38_Smalltit.h"
#include "Type_Unk_F0E20x.h"
#include "Type_WORD_D951C.h"
#include "XUnk_D4350.h"
#include "Type_D404C.h"
#include "Type_D94F0_Bldgprmbuffer.h"
#include "Type_D93C0_Bldgprmbuffer.h"
#include "TextureMaps.h"
#include "defs.h"
#include "RenderThread.h"
#include "ProjectionPolygon.h"

typedef struct {
	int32_t r0;
	int32_t r1;
	int32_t r2;
	int32_t r3;
	int32_t r4;
} Rasterline_t;

constexpr int MAX_THREADS = 8;
constexpr int MAX_RASTERLINES = 209716; // based on the original 2048 * 2048 / 20 bytes per Rasterline_t, can probably be reduced (to screen height + margin?)


class GameRenderHD : public GameRenderInterface
{

private:

	//The sprite render uses hardcoded offsets of the buffer. This have been adjusted to the new buffer size of
	//m_ptrDWORD_E9C38_smalltit otherwise at higher resolutions sprite data they writes over each other
	const int m_bufferOffset_E9C38_1 = 995328; // 12%
	const int m_bufferOffset_E9C38_2 = 1161216; // 14%
	const int m_bufferOffset_E9C38_3 = 1658880; // 20%

	uint8_t unk_D4328x[40] = {
		0xED,0x01,0x00,0x00,0x00,0xFF,0xD8,0xFF,0x01,0x00,0x00,0xED,0xFF,0x00,0x01,0x00,
		0x01,0xD8,0x00,0x01,0x13,0x00,0xFF,0xFF,0x00,0x01,0x28,0x01,0xFF,0x00,0x01,0x13,
		0x00,0xFF,0xFF,0x00,0xFF,0x28,0x00,0xFF
	};

	std::array<std::array<Rasterline_t, MAX_RASTERLINES>, MAX_THREADS> rasterlines_DE56Cx;
	
	char x_BYTE_D4750[60] = {
		0x00,0x00,0x02,0x03,0x04,0x05,0x01,0x00,0x06,0x07,0x04,0x05,0x00,0x01,0x01,0x02,
		0x02,0x03,0x03,0x04,0x04,0x03,0x03,0x02,0x02,0x01,0x01,0x00,0x00,0x00,0x00,0x01,
		0x01,0x01,0x02,0x02,0x02,0x02,0x02,0x01,0x01,0x01,0x00,0x00,0x03,0x03,0x03,0x03,
		0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0C,0x0C,0x0C
	};

	type_unk_F0E20x m_str_F0E20x[GAME_RES_MAX_WIDTH + 100]; // Originally 640

	uint8_t* m_ptrDWORD_E9C38_smalltit = nullptr;
	uint8_t* m_ptrScreenBuffer_351628 = nullptr;
	uint8_t* m_ptrColorPalette = nullptr;
	uint8_t* m_preBlurBuffer_E9C3C = nullptr;
	uint8_t* m_ptrBlurBuffer_E9C3C = nullptr;

	std::vector<RenderThread*> m_renderThreads;
	bool m_multiThreadRender = false;
	bool m_assignToSpecificCores = false;

	int x_DWORD_D4794 = 0;
	int x_DWORD_D4798 = 0;
	char x_BYTE_E126D = 0;     // 7: reflections off, 5: reflections on
	char x_BYTE_E126C = 112;
	int x_DWORD_D4790 = 20;
	int x_DWORD_D4324 = 0;
	char shadows_F2CC7 = 0;
	char notDay_D4320 = 0;
	char x_BYTE_F2CC6 = 0;
	int16_t yaw_F2CC0 = 0;
	int16_t x_WORD_F2CC2 = 0;
	int16_t x_WORD_F2CC4 = 0;

	uint8_t* x_DWORD_DE55C_ActTexture = 0;

	void DrawSky_40950(int16_t roll, uint8_t startLine, uint8_t drawEveryNthLine);
	void DrawSky_40950_TH(int16_t roll);
	void DrawTerrainAndParticles_3C080(__int16 posX, __int16 posY, __int16 yaw, signed int posZ, int pitch, int16_t roll, int fov);
	void SubDrawTerrainAndParticles(std::vector<int>& projectedVertexBuffer, int pitch);
	void SubDrawInverseTerrainAndParticles(std::vector<int>& projectedVertexBuffer, int pitch);
	void SubDrawCaveTerrainAndParticles(std::vector<int>& projectedVertexBuffer, int pitch);
	void DrawSprite_41BD3(uint32 a1);
	void DrawSquareInProjectionSpace(std::vector<int>& vertexs, int index);
	void DrawInverseSquareInProjectionSpace(int* vertexs, int index);
	void DrawInverseSquareInProjectionSpace(int* vertexs, int index, uint8_t* pTexture);
	void DrawSprites_3E360(int a2x, type_particle_str** str_DWORD_F66F0x[], uint8_t x_BYTE_E88E0x[], int32_t x_DWORD_F5730[], type_event_0x6E8E* x_DWORD_EA3E4[], type_str_unk_1804B0ar str_unk_1804B0ar, ViewPort viewPort, uint16_t screenWidth);
	void DrawTriangleInProjectionSpace_B6253(const ProjectionPolygon* vertex1, const ProjectionPolygon* vertex2, const ProjectionPolygon* vertex3, uint8_t startLine, uint8_t drawEveryNthLine);
	Rasterline_t* RasterizePolygon(Rasterline_t* ptrPolys, int* v0, int* v1, int s0, int s1, int* line);
	Rasterline_t* RasterizePolygon(Rasterline_t* ptrPolys, int* v0, int* v1, int* v4, int s0, int s1, int s4, int* line);
	Rasterline_t* RasterizePolygon(Rasterline_t* ptrPolys, int* v0, int* v1, int* v2, int* v3, int s0, int s1, int s2, int s3, int* line);
	Rasterline_t* RasterizePolygon(Rasterline_t* ptrPolys, int* v0, int* v1, int* v2, int* v3, int* v4, int s0, int s1, int s2, int s3, int s4, int* line);
	uint16_t sub_3FD60(int a2x, uint8_t x_BYTE_E88E0x[], type_event_0x6E8E* x_DWORD_EA3E4[], type_str_unk_1804B0ar str_unk_1804B0ar, type_particle_str** str_DWORD_F66F0x[], int32_t x_DWORD_F5730[], ViewPort viewPort, uint16_t screenWidth);
	void sub_88740(type_event_0x6E8E* a1, int16_t posX, int16_t posY);
	void SetBillboards_3B560(int16_t roll);
	void DrawSorcererNameAndHealthBar_2CB30(type_event_0x6E8E* a1, __int16 a2, int a3, __int16 a4);
	void StartWorkerThreads(uint8_t numOfThreads, bool assignToSpecificCores);
	void StartWorkerThread();
	void StartWorkerThread(int core);
	void StopWorkerThreads();
	void WaitForRenderFinish();

public:
	GameRenderHD(uint8_t* ptrScreenBuffer, uint8_t* pColorPalette, uint8_t renderThreads, bool assignToSpecificCores);
	~GameRenderHD();
	
	void SetRenderThreads(uint8_t renderThreads);
	uint8_t GetRenderThreads();

	void DrawWorld_411A0(int posX, int posY, int16_t yaw, int16_t posZ, int16_t pitch, int16_t roll, int16_t fov);
	void WriteWorldToBMP();
	void WriteWholeBufferToBmp();
	void ClearGraphicsBuffer(uint8_t colorIdx);

	static int32_t CalculateRotationTranslationX(int64_t cos_0x11, int64_t pnt1, int64_t sin_0x0d, int64_t pnt2);
	static int32_t CalculateRotationTranslationY(int64_t pnt1, int64_t sin_0x0d, int64_t cos_0x11, int64_t pnt2);
};

#endif //GAME_RENDER_HD