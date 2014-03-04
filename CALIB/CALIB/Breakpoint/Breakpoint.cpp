#include "Breakpoint.h"

extern "C"
{
	DWORD cBreakpoint::dwAddress1, cBreakpoint::dwAddress2, cBreakpoint::dwAddress3, cBreakpoint::dwAddress4;
	DWORD cBreakpoint::dwEIP1, cBreakpoint::dwEIP2, cBreakpoint::dwEIP3, cBreakpoint::dwEIP4;

	cBreakpoint::cBreakpoint(DWORD ThreadID)
	{
		hwBP = AddVectoredExceptionHandler(rand() % 10000, ExceptionFilter);

		if (ThreadID)
			thread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, 1, ThreadID);
		else
			GetMainThreadFromCurrentProcess();

		dwAddress1 = dwAddress2 = dwAddress3 = dwAddress4 = NULL;
		dwEIP1 = dwEIP2 = dwEIP3 = dwEIP4 = NULL;
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

	void cBreakpoint::Disable()
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
	}

	void cBreakpoint::Enable()
	{
		SuspendThread(thread);

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

	LONG WINAPI cBreakpoint::ExceptionFilter(EXCEPTION_POINTERS* ExceptionInfo)
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
}