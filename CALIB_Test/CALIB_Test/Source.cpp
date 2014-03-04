#include "CALIB.h"
cBreakpoint* Breakpoint1 = NULL;

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

DWORD dwSuperBulletsJMP;
__declspec(naked) void __stdcall vSuperBullets()
{
	__asm JMP dwSuperBulletsJMP;
}

bool bSuperJump = false;
DWORD _stdcall dwBreakpoint1Thread(LPVOID)
{
	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);

	Memory = new cMemory();

	Breakpoint1 = new cBreakpoint();

	dwFireWeaponJMP = Memory->ADDRESS_FIREWEAPON + 1;
	Breakpoint1->SetBreakPoint1(Memory->ADDRESS_FIREWEAPON, DWORD(&vFireWeapon));

	dwAmmoJMP = Memory->ADDRESS_AMMO + 0xB;
	Breakpoint1->SetBreakPoint2(Memory->ADDRESS_AMMO, DWORD(&vAmmo));

	dwSuperBulletsJMP = Memory->ADDRESS_SUPERBULLETS + 3;
	Breakpoint1->SetBreakPoint3(Memory->ADDRESS_SUPERBULLETS, DWORD(&vSuperBullets));

	Breakpoint1->Enable();

	while (1)
	{
		*(float*)Memory->ADDRESS_PICKUPDISTANCE = 999999999.0f;

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{

		}
		*(float*)Memory->ADDRESS_JUMPVEL = 999999999.0f;
		Sleep(50);
	}

	return NULL;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Strings = new cStrings();
		CreateThread(0, 0, dwBreakpoint1Thread, 0, 0, 0);
	}

	return true;
}