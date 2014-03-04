#include "CALIB.h"

DWORD dwAmmoJMP;
__declspec(naked) void __stdcall vAmmo()
{
	__asm JMP dwAmmoJMP;
}

LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* ExceptionInfo)
{
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	{
		if (dwAddress1 != NULL && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == dwAddress1)
		{
			ExceptionInfo->ContextRecord->Eip = dwEIP1;
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		if (dwAddress2 != NULL && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == dwAddress2)
		{
			ExceptionInfo->ContextRecord->Eip = dwEIP2;
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		if (dwAddress3 != NULL && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == dwAddress3)
		{
			ExceptionInfo->ContextRecord->Eip = dwEIP3;
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		if (dwAddress4 != NULL && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == dwAddress4)
		{
			ExceptionInfo->ContextRecord->Eip = dwEIP4;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

cBreakpoint* Breakpoint;
DWORD _stdcall dwStart(LPVOID)
{
	Strings = new cStrings();
	Breakpoint = new cBreakpoint();

	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);

	Memory = new cMemory();

	dwAmmoJMP = Memory->ADDRESS_AMMO + 0xB;
	Breakpoint->SetBreakPoint1(Memory->ADDRESS_AMMO, DWORD(&vAmmo));

	char* buf = new char[256];
	sprintf(buf, "0x%X : 0x%X", Memory->ADDRESS_AMMO, dwAmmoJMP);
	MessageBox(0, buf, 0, 0);
	delete[] buf;

	Breakpoint->SetBreakPoints();

	return NULL;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, dwStart, 0, 0, 0);

	return true;
}