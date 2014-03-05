#ifndef _DIRECTX_
#define _DIRECTX_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include "Font\Font.h"

struct D3DTLVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	D3DCOLOR Color;
	float fU;
	float fV;
};

struct DXUT_SCREEN_VERTEX
{
	float x, y, z, h;
	D3DCOLOR color;
	float tu, tv;
	static DWORD FVF;
};

enum gr_orientation 
{
	horizontal,
	vertical
};

class cDirectx
{
private:
	cFont* Font;

public:
	DWORD dwEndScene, dwReset, dwDIP;
	cDirectx();

	LPDIRECT3DDEVICE9 g_pDevice;
	LPD3DXFONT pFont;

	D3DVIEWPORT9 viewport;

	void HookEndscene(PBYTE es);
	void HookDIP(PBYTE dip);
	void HookReset(PBYTE rs);

	void RenderString(int x, int y, DWORD color, char* text);

	bool Checks(LPDIRECT3DDEVICE9 pDevice);
	HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32);
	void DrawCrosshair(int size, D3DCOLOR xcolor);
	void DrawLine(float X, float Y, float X2, float Y2, DWORD dwColor);
	void DrawFilledRectangle(float x, float y, float w, float h, DWORD dwColor);
	void DrawNonFilledRectangle(float x, float y, float w, float h, DWORD dwColor);
	void DrawBorder(float x, float y, float w, float h, DWORD color1, DWORD color2);
	void DrawBorderWithFill(float x, float y, float w, float h, DWORD color1, DWORD color2, DWORD Fill);
	void PrintText(long x, long y, D3DCOLOR fontColor, char *text, ...);
	void GradientRect(float x, float y, float width, float height, DWORD startCol, DWORD endCol, gr_orientation orientation);
	bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, const D3DXVECTOR3& WorldPos, D3DXVECTOR3* pScreenPos);
	void Draw2DCircle(POINT pt, float radius, D3DCOLOR color);

	typedef HRESULT(WINAPI* tEndscene) (LPDIRECT3DDEVICE9);
	tEndscene pEndscene;

	typedef HRESULT(WINAPI* tDIP) (LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE, int, UINT, UINT, UINT, UINT);
	tDIP pDIP;
	IDirect3DVertexBuffer9* pStreamData;
	UINT PSizeOfData, OffsetInBytes, Stride;
}; extern cDirectx* Directx;

#endif