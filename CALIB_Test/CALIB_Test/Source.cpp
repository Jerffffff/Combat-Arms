#include "CALIB.h"
cBreakpoint* Breakpoint;

DWORD dwAmmoJMP;
__declspec(naked) void __stdcall vAmmo()
{
	__asm JMP dwAmmoJMP;
}

LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* ExceptionInfo)
{
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	{
		if (Breakpoint->dwAddress1 != NULL && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == Breakpoint->dwAddress1)
		{
			ExceptionInfo->ContextRecord->Eip = Breakpoint->dwEIP1;
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		if (Breakpoint->dwAddress2 != NULL && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == Breakpoint->dwAddress2)
		{
			ExceptionInfo->ContextRecord->Eip = Breakpoint->dwEIP2;
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		if (Breakpoint->dwAddress3 != NULL && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == Breakpoint->dwAddress3)
		{
			ExceptionInfo->ContextRecord->Eip = Breakpoint->dwEIP3;
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		if (Breakpoint->dwAddress4 != NULL && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == Breakpoint->dwAddress4)
		{
			ExceptionInfo->ContextRecord->Eip = Breakpoint->dwEIP4;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

DWORD _stdcall dwStart(LPVOID)
{
	Strings = new cStrings();
	Breakpoint = new cBreakpoint();

	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);

	Memory = new cMemory();
	dwAmmoJMP = Memory->ADDRESS_AMMO + 0xB;
	char* buf = new char[256];
	sprintf(buf, "0x%X : 0x%X", Memory->ADDRESS_AMMO, dwAmmoJMP);
	MessageBox(0, buf, 0, 0);
	delete[] buf;

	Breakpoint->SetBreakPoint1(Memory->ADDRESS_AMMO, DWORD(&vAmmo));

	Breakpoint->SetBreakPoints(ExceptionFilter);

	return NULL;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, dwStart, 0, 0, 0);

	return true;
}