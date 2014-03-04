#include "CALIB.h"

DWORD _stdcall dwStart(LPVOID)
{
	Strings = new cStrings();

	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);

	Memory = new cMemory();

	return NULL;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, dwStart, 0, 0, 0);

	return true;
}