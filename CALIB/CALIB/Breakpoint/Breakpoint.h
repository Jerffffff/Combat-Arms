#ifndef _BREAKPOINT_
#define _BREAKPOINT_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>

class cBreakpoint
{
private:
	HANDLE thread;
	CONTEXT thread_context;
	static DWORD dwAddress1, dwAddress2, dwAddress3, dwAddress4;
	static  DWORD dwEIP1, dwEIP2, dwEIP3, dwEIP4;
	PVOID hwBP;
	void GetMainThreadFromCurrentProcess();
public:
	cBreakpoint(DWORD ThreadID = NULL);

	static LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* ExceptionInfo);

	void SetBreakPoint1(DWORD dwAddress, DWORD dwEIP);
	void SetBreakPoint2(DWORD dwAddress, DWORD dwEIP);
	void SetBreakPoint3(DWORD dwAddress, DWORD dwEIP);
	void SetBreakPoint4(DWORD dwAddress, DWORD dwEIP);

	void Enable();
	void Disable();
};

#endif