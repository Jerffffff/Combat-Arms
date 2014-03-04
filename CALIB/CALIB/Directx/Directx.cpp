#include "Directx.h"

extern "C"
{
	cDirectx* Directx;

	cDirectx::cDirectx()
	{
		Font = new cFont();
	}

	void cDirectx::RenderString(int x, int y, DWORD color, char* text)
	{
		Font->RenderString(x, y, color, text);
	}
}