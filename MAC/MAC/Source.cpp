#include "HWID.h"
#include <iostream>

void toClipboard(HWND hwnd, const string &s)
{
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg)
	{
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

int main()
{
	HWID = new cHWID();
	toClipboard(GetDesktopWindow(), HWID->sHWID);

	std::cout << "Your ID has been copied to your clipboard, paste it to me!\n";

	system("pause");

	return 1;
}