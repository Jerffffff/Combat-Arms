#include "Directx.h"
#include "../Strings/Strings.h"
#include "../Detours/Detours.h"

extern "C"
{
	cDirectx* Directx;

	cDirectx::cDirectx()
	{
		//Font = new cFont();

		MODULEINFO mInfo;
		DWORD dwD3D9 = NULL;

		OSVERSIONINFO WindowsVersion;
		WindowsVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&WindowsVersion);
		if (WindowsVersion.dwMajorVersion < 5 && WindowsVersion.dwMinorVersion >= 3)
		{
			MessageBox(NULL, Strings->OS_NOT_SUPPORTED, NULL, NULL);
			TerminateProcess(GetCurrentProcess(), 0);
		}

		while (!dwD3D9)
			dwD3D9 = (DWORD)GetModuleHandle(Strings->MODULE_D3D9);

		GetModuleInformation(GetCurrentProcess(), (HMODULE)dwD3D9, &mInfo, sizeof(MODULEINFO));

		if (WindowsVersion.dwMajorVersion == 6 && WindowsVersion.dwMinorVersion == 2)//Windows 8
		{
			dwDIP = (int)mInfo.EntryPoint + 0xFFFFFFFFFFFE95B7;
			dwEndScene = (int)mInfo.EntryPoint + 0xFFFFFFFFFFFDF736;
			dwReset = (int)mInfo.EntryPoint + 0xFFFFFFFFFFFF28E6;
		}
		else if (WindowsVersion.dwMajorVersion == 6 && WindowsVersion.dwMinorVersion == 1)//Windows 7  
		{
			dwEndScene = (int)mInfo.EntryPoint + 0x20D5A;
			dwDIP = (int)mInfo.EntryPoint + 0x29C6C;
			dwReset = (int)mInfo.EntryPoint + 0x5D80C;
		}
		else if (WindowsVersion.dwMajorVersion == 5 && WindowsVersion.dwMinorVersion == 1)//Windows XP
		{
			dwEndScene = (int)mInfo.EntryPoint + 0x7A2E;
			dwReset = (int)mInfo.EntryPoint + 0xFFFFFFFFFFFC3F2E;
		}
	}

	void cDirectx::HookEndscene(PBYTE es)
	{
		pEndscene = (tEndscene)DetourFunction(PBYTE(dwEndScene), es);
	}

	void cDirectx::HookDIP(PBYTE dip)
	{
		pDIP = (tDIP)DetourFunction(PBYTE(dwDIP), dip);
	}

	void cDirectx::HookReset(PBYTE rs)
	{
		//pReset = (tReset)DetourFunction(PBYTE(dwReset), pbReset);
	}

	void cDirectx::RenderString(int x, int y, DWORD color, char* text)
	{
		Font->RenderString(x, y, color, text);
	}

	void cDirectx::DrawCrosshair(int size, D3DCOLOR xcolor)
	{
		D3DRECT rec2 = { (viewport.Width-1) - size, (viewport.Height-1), (viewport.Width-1) + size, (viewport.Height-1) + 1 };
		D3DRECT rec3 = { (viewport.Width-1), (viewport.Height-1) - size, (viewport.Width-1) + 1, (viewport.Height-1) + size };
		pDevice->Clear(1, &rec2, D3DCLEAR_TARGET, xcolor, 1000, 0);
		pDevice->Clear(1, &rec3, D3DCLEAR_TARGET, xcolor, 100, 0);
	}

	HRESULT cDirectx::GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
	{
		if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
			return E_FAIL;

		WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
			| (WORD)(((colour32 >> 20) & 0xF) << 8)
			| (WORD)(((colour32 >> 12) & 0xF) << 4)
			| (WORD)(((colour32 >> 4) & 0xF) << 0);

		D3DLOCKED_RECT d3dlr;
		(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
		WORD *pDst16 = (WORD*)d3dlr.pBits;

		for (int xy = 0; xy < 8 * 8; xy++)
			*pDst16++ = colour16;

		(*ppD3Dtex)->UnlockRect(0);

		return S_OK;
	}
}