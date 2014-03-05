#include "Directx.h"
#include "../Strings/Strings.h"
#include "../Detours/Detours.h"

#define D3DFVF_TL (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

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

	bool cDirectx::Checks(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->GetViewport(&viewport);

		return g_pDevice == pDevice;
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
		D3DRECT rec2 = { (viewport.Width/2) - 1 - size, (viewport.Height/2) - 1, (viewport.Width/2) - 1 + size, (viewport.Height/2) - 1 + 1 };
		D3DRECT rec3 = { (viewport.Width/2) - 1, (viewport.Height/2) - 1 - size, (viewport.Width/2) - 1 + 1, (viewport.Height/2) - 1 + size };
		g_pDevice->Clear(1, &rec2, D3DCLEAR_TARGET, xcolor, 1000, 0);
		g_pDevice->Clear(1, &rec3, D3DCLEAR_TARGET, xcolor, 100, 0);
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

	void cDirectx::DrawFilledRectangle(float x, float y, float w, float h, DWORD dwColor)
	{
		DXUT_SCREEN_VERTEX vertices[4] =
		{
			x, y, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
			x + w, y, 0.0f, 1.0f, dwColor, 1.0f, 0.0f,

			x + w, y + h, 0.0f, 1.0f, dwColor, 1.0f, 1.0f,
			x, y + h, 0.0f, 1.0f, dwColor, 0.0f, 1.0f,
		};
		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(DXUT_SCREEN_VERTEX));
	}

	void cDirectx::GradientRect(float x, float y, float width, float height, DWORD startCol, DWORD endCol, gr_orientation orientation)
	{
		static struct D3DVERTEX { float x, y, z, rhw; DWORD color; } vertices[4] = { { 0, 0, 0, 1.0f, 0 }, { 0, 0, 0, 1.0f, 0 }, { 0, 0, 0, 1.0f, 0 }, { 0, 0, 0, 1.0f, 0 } };
		vertices[0].x = x;
		vertices[0].y = y;
		vertices[0].color = startCol;

		vertices[1].x = x + width;
		vertices[1].y = y;
		vertices[1].color = orientation == horizontal ? endCol : startCol;

		vertices[2].x = x;
		vertices[2].y = y + height;
		vertices[2].color = orientation == horizontal ? startCol : endCol;

		vertices[3].x = x + width;
		vertices[3].y = y + height;
		vertices[3].color = endCol;


		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		g_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
	}

	void cDirectx::DrawNonFilledRectangle(float x, float y, float w, float h, DWORD dwColor)
	{
		DXUT_SCREEN_VERTEX vertices[6] =
		{
			x + w, y, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
			x + w, y + h, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
			x, y + h, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,

			x, y + h, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
			x, y, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
			x + w, y, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
		};
		g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 5, vertices, sizeof(DXUT_SCREEN_VERTEX));
	}

	void cDirectx::DrawLine(float X, float Y, float X2, float Y2, DWORD dwColor)
	{
		D3DTLVERTEX qV[2] =
		{
			{ (float)X, (float)Y, 0.0f, 1.0f, dwColor },
			{ (float)X2, (float)Y2, 0.0f, 1.0f, dwColor },
		};
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, qV, sizeof(D3DTLVERTEX));
	}

	void cDirectx::DrawBorder(float x, float y, float w, float h, DWORD color1, DWORD color2)
	{
		DXUT_SCREEN_VERTEX vertices[6] =
		{
			x + w, y, 0.0f, 1.0f, color2, 0, 0,
			x + w, y + h, 0.0f, 1.0f, color2, 0, 0,
			x, y + h, 0.0f, 1.0f, color2, 0, 0,

			x, y + h, 0.0f, 1.0f, color1, 0, 0,
			x, y, 0.0f, 1.0f, color1, 0, 0,
			x + w, y, 0.0f, 1.0f, color1, 0, 0,
		};
		g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 5, vertices, sizeof(DXUT_SCREEN_VERTEX));
	}

	void cDirectx::DrawBorderWithFill(float x, float y, float w, float h, DWORD color1, DWORD color2, DWORD Fill)
	{
		DXUT_SCREEN_VERTEX vertices[6] =
		{
			x + w, y, 0.0f, 1.0f, color2, 0, 0,
			x + w, y + h, 0.0f, 1.0f, color2, 0, 0,
			x, y + h, 0.0f, 1.0f, color2, 0, 0,

			x, y + h, 0.0f, 1.0f, color1, 0, 0,
			x, y, 0.0f, 1.0f, color1, 0, 0,
			x + w, y, 0.0f, 1.0f, color1, 0, 0,
		};
		g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 5, vertices, sizeof(DXUT_SCREEN_VERTEX));
		DrawFilledRectangle(x + 1, y + 1, w - 1, h - 1, Fill);
	}

	D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
	{
		D3DTLVERTEX v;

		v.fX = X;
		v.fY = Y;
		v.fZ = Z;
		v.fRHW = RHW;
		v.Color = color;
		v.fU = U;
		v.fV = V;

		return v;
	}

	void cDirectx::Draw2DCircle(POINT pt, float radius, D3DCOLOR color)
	{
		const int NUMPOINTS = 24;
		const float PI = 3.14159f;
		D3DTLVERTEX Circle[NUMPOINTS + 1];
		int i;
		float X;
		float Y;
		float Theta;
		float WedgeAngle; //Size of angle between two points on the circle (single wedge)
		//Precompute WedgeAngle
		WedgeAngle = (float)((2 * PI) / NUMPOINTS);
		//Set up vertices for a circle
		//Used <= in the for statement to ensure last point meets first point (closed circle)
		for (i = 0; i <= NUMPOINTS; i++)
		{
			//Calculate theta for this vertex
			Theta = i * WedgeAngle;

			//Compute X and Y locations
			X = (float)(pt.x + radius * cos(Theta));
			Y = (float)(pt.y - radius * sin(Theta));
			Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f);
		}
		//Now draw the circle
		g_pDevice->SetFVF(D3DFVF_TL);
		g_pDevice->SetTexture(0, NULL);
		//g_pDevice->SetVertexShader (D3DFVF_MIRUSVERTEX);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));
	}

	void cDirectx::PrintText(long x, long y, D3DCOLOR fontColor, char *text, ...)
	{
		RECT rct;
		rct.left = x - 1;
		rct.right = x + 1;
		rct.top = y - 1;
		rct.bottom = y + 1;

		if (!text) return;
		va_list va_alist;
		char logbuf[256] = { 0 };
		va_start(va_alist, text);
		_vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf)-strlen(logbuf), text, va_alist);
		va_end(va_alist);
		RECT FontRect = { x, y, x, y };
		pFont->DrawTextA(NULL, logbuf, -1, &rct, DT_NOCLIP, fontColor);
	}
}