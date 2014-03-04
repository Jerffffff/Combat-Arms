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

DWORD _stdcall dwBreakpoint1Thread(LPVOID)
{
	while (1)
	{
		if (!Breakpoint1)
		{
			Breakpoint1 = new cBreakpoint(GetCurrentThread());

			dwFireWeaponJMP = Memory->ADDRESS_FIREWEAPON + 1;
			Breakpoint1->SetBreakPoint1(Memory->ADDRESS_FIREWEAPON, DWORD(&vFireWeapon));

			dwAmmoJMP = Memory->ADDRESS_AMMO + 0xB;
			Breakpoint1->SetBreakPoint2(Memory->ADDRESS_AMMO, DWORD(&vAmmo));

			Breakpoint1->Enable();

			MessageBox(0, 0, 0, 0);
		}
	}

	return NULL;
}

bool bEnabled = false;
DWORD _stdcall dwMainThread(LPVOID)
{
	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);

	Memory = new cMemory();

	CreateThread(0, 0, dwBreakpoint1Thread, 0, 0, 0);
	Sleep(1000);

	while (1)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			bEnabled = !bEnabled;
			if (bEnabled)
				Breakpoint1->Enable();
			else
				Breakpoint1->Disable();
		}

		Sleep(100);
	}

	return NULL;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Strings = new cStrings();
		CreateThread(0, 0, dwMainThread, 0, 0, 0);
	}

	return true;
}