#include "CALIB.h"
cBreakpoint* Breakpoint;

DWORD dwFireWeaponJMP;
__declspec(naked) void __stdcall vFireWeapon()
{
	static ILTMessage_Read* pMsg;
	__asm
	{
		PUSHAD;
		PUSHFD;
		MOV pMsg, EAX
	}

	if (pMsg->Size() > 900)
		pMsg = pMsg->SubMsg(0, 800);
	else
		pMsg = pMsg->SubMsg(0, 600);

	_asm
	{
		POPFD;
		POPAD;

		PUSH pMsg;
		JMP dwFireWeaponJMP;
	}
}

DWORD dwAmmoJMP;
__declspec(naked) void __stdcall vAmmo()
{
	__asm JMP dwAmmoJMP;
}

DWORD _stdcall dwStart(LPVOID)
{
	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);

	Memory = new cMemory();

	dwFireWeaponJMP = Memory->ADDRESS_FIREWEAPON + 1;
	Breakpoint->SetBreakPoint1(Memory->ADDRESS_FIREWEAPON, DWORD(&vFireWeapon));

	dwAmmoJMP = Memory->ADDRESS_AMMO + 0xB;
	Breakpoint->SetBreakPoint2(Memory->ADDRESS_AMMO, DWORD(&vAmmo));

	Breakpoint->SetBreakPoints();

	return NULL;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Breakpoint = new cBreakpoint();
		Strings = new cStrings();
		CreateThread(0, 0, dwStart, 0, 0, 0);
	}

	return true;
}