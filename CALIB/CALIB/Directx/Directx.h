#ifndef _DIRECTX_
#define _DIRECTX_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include "Font\Font.h"

class cDirectx
{
private:
	cFont* Font;

public:
	DWORD dwEndScene, dwReset, dwDIP;
	cDirectx();

	LPDIRECT3DDEVICE9 pDevice, g_pDevice;

	D3DVIEWPORT9 viewport;

	void HookEndscene(PBYTE es);
	void HookDIP(PBYTE dip);
	void HookReset(PBYTE rs);

	void RenderString(int x, int y, DWORD color, char* text);

	HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32);
	void DrawCrosshair(int size, D3DCOLOR xcolor);

	typedef HRESULT(WINAPI* tEndscene) (LPDIRECT3DDEVICE9);
	tEndscene pEndscene;

	typedef HRESULT(WINAPI* tDIP) (LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE, int, UINT, UINT, UINT, UINT);
	tDIP pDIP;
	IDirect3DVertexBuffer9* pStreamData;
	UINT PSizeOfData, OffsetInBytes, Stride;
}; extern cDirectx* Directx;

#endif