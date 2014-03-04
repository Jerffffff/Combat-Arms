#include "Breakpoint.h"

extern "C"
{
	cBreakpoint::cBreakpoint()
	{
		thread = NULL;
		dwAddress1 = dwAddress2 = dwAddress3 = dwAddress4 = NULL;
		dwEIP1 = dwEIP2 = dwEIP3 = dwEIP4 = NULL;
		handler = NULL;
		hwBP = NULL;
	}

	void cBreakpoint::GetMainThreadFromCurrentProcess()
	{
		unsigned long uProcessId = GetCurrentProcessId();
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, uProcessId);

		if (!hSnapshot)
			return;

		THREADENTRY32 lpThread;

		lpThread.dwSize = sizeof(THREADENTRY32);

		if (Thread32First(hSnapshot, &lpThread))
		{
			do
			{
				if (lpThread.th32OwnerProcessID == uProcessId)
					break;
			} while (Thread32Next(hSnapshot, &lpThread));

			CloseHandle(hSnapshot);
			thread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, 1, lpThread.th32ThreadID);
		}
	}

	void cBreakpoint::SetBreakPoint1(DWORD dwAddress, DWORD dwEIP)
	{
		dwAddress1 = dwAddress;
		dwEIP1 = dwEIP;
	}

	void cBreakpoint::SetBreakPoint2(DWORD dwAddress, DWORD dwEIP)
	{
		dwAddress2 = dwAddress;
		dwEIP2 = dwEIP;
	}

	void cBreakpoint::SetBreakPoint3(DWORD dwAddress, DWORD dwEIP)
	{
		dwAddress3 = dwAddress;
		dwEIP3 = dwEIP;
	}

	void cBreakpoint::SetBreakPoint4(DWORD dwAddress, DWORD dwEIP)
	{
		dwAddress4 = dwAddress;
		dwEIP4 = dwEIP;
	}

	void cBreakpoint::UnsetBreakPoints()
	{
		SuspendThread(thread);
		thread_context = { CONTEXT_DEBUG_REGISTERS };
		thread_context.Dr0 = NULL;
		thread_context.Dr1 = NULL;
		thread_context.Dr2 = NULL;
		thread_context.Dr3 = NULL;
		thread_context.Dr7 = NULL;
		SetThreadContext(thread, &thread_context);
		ResumeThread(thread);
		CloseHandle(thread);
		thread = NULL;
		RemoveVectoredExceptionHandler(hwBP);
	}

	void cBreakpoint::SetBreakPoints(PVECTORED_EXCEPTION_HANDLER pHandler, HANDLE hThread)
	{
		hThread != NULL ? thread = hThread : GetMainThreadFromCurrentProcess();
		SuspendThread(thread);
		hwBP = AddVectoredExceptionHandler(rand() % 10000, pHandler);

		thread_context = { CONTEXT_DEBUG_REGISTERS };
		thread_context.Dr0 = dwAddress1;
		thread_context.Dr1 = dwAddress2;
		thread_context.Dr2 = dwAddress3;
		thread_context.Dr3 = dwAddress4;
		thread_context.Dr7 = dwAddress4 != NULL ? (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6) :
			dwAddress3 != NULL ? (1 << 0) | (1 << 2) | (1 << 4) :
			dwAddress2 != NULL ? (1 << 0) | (1 << 2) :
			dwAddress1 != NULL ? (1 << 0) : NULL;
		SetThreadContext(thread, &thread_context);
		ResumeThread(thread);
	}
}