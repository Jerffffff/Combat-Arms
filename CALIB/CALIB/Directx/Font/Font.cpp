#include "Font.h"

extern "C"
{
	cFont::cFont()
	{
		pFont = (cEFont*)BuildFontByFontIndex(24, 12);
	}

	int cFont::GetFontHandle(int index)
	{
		void* vGetFontHandle = (void*)Memory->ADDRESS_GETFONTHANDLE;
		DWORD dwECX = *(DWORD*)Memory->ADDRESS_FONTECX;

		__asm
		{
			push 0
			push index
			mov ecx, dwECX
			call[vGetFontHandle]
		}
	}

	DWORD cFont::BuildFontByFontIndex(int index, int FontSize)
	{
		void* vBuildFont = (void*)Memory->ADDRESS_BUILDFONT;
		void* dwFill = (void*)Memory->ADDRESS_FILLFONT;
		int FontHandle = GetFontHandle(index);
		DWORD dwFontAddr = 0;
		BYTE* FontBuffer = new BYTE[0x228];

		__asm
		{
			mov ecx, FontBuffer
			call[dwFill]
			mov dwFontAddr, eax
			mov ecx, eax
			push	0
			push	0
			push	0
			push	0
			push	FontSize
			push	FontHandle
			push	0
			push	0
			push	0
			call[vBuildFont]
		}

		return dwFontAddr;
	}

	void cFont::RenderString(int x, int y, DWORD color, char* text)
	{
		if (pFont)
		{
			pFont->SetText((unsigned short*)text, 1);
			pFont->SetPos(x, y);
			pFont->SetColor(color, color, color, (int)-1);
			pFont->Render();
		}
	}
}