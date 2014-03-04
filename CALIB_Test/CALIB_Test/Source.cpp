#include "CALIB.h"

DWORD dwAmmoJMP;
__declspec(naked) void __stdcall vAmmo()
{
	__asm JMP dwAmmoJMP;
}

cBreakpoint* Breakpoint;
DWORD _stdcall dwStart(LPVOID)
{
	Strings = new cStrings();

	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);

	Memory = new cMemory();

	Breakpoint = new cBreakpoint();
	dwAmmoJMP = Memory->ADDRESS_AMMO + 0xB;
	Breakpoint->SetBreakPoint1(Memory->ADDRESS_AMMO, DWORD(&vAmmo));

	return NULL;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, dwStart, 0, 0, 0);

	return true;
}