#ifndef _BREAKPOINT_
#define _BREAKPOINT_

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>

class cBreakpoint
{
private:
	HANDLE thread;
	CONTEXT thread_context;
	DWORD dwAddress1, dwAddress2, dwAddress3, dwAddress4;
	DWORD dwEIP1, dwEIP2, dwEIP3, dwEIP4;
	PVOID hwBP;
	PVECTORED_EXCEPTION_HANDLER handler;
	void GetMainThreadFromCurrentProcess();
public:
	cBreakpoint();

	void SetBreakPoint1(DWORD dwAddress, DWORD dwEIP);
	void SetBreakPoint2(DWORD dwAddress, DWORD dwEIP);
	void SetBreakPoint3(DWORD dwAddress, DWORD dwEIP);
	void SetBreakPoint4(DWORD dwAddress, DWORD dwEIP);

	void SetBreakPoints(PVECTORED_EXCEPTION_HANDLER pHandler, HANDLE hThread = NULL);
	void UnsetBreakPoints();
};

#endif