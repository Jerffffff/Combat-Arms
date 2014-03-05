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

	void HookEndscene(PBYTE es);
	void HookDIP(PBYTE dip);
	void HookReset(PBYTE rs);

	void RenderString(int x, int y, DWORD color, char* text);

	typedef HRESULT(WINAPI* tEndscene) (LPDIRECT3DDEVICE9);
	tEndscene pEndscene;

	typedef HRESULT(WINAPI* tDIP) (LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE, int, UINT, UINT, UINT, UINT);
	tDIP pDIP;
	IDirect3DVertexBuffer9* pStreamData;
	UINT PSizeOfData, OffsetInBytes, Stride;
}; extern cDirectx* Directx;

#endif