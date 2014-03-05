#include "Directx.h"
#include "../Strings/Strings.h"
#include "../Detours/Detours.h"

extern "C"
{
	cDirectx* Directx;

	cDirectx::cDirectx(PBYTE pbEndscene, PBYTE pbReset, PBYTE pbDIP)
	{
		Font = new cFont();

		MODULEINFO mInfo;
		DWORD dwD3D9 = NULL;
		DWORD dwEndScene, dwReset, dwDIP;

		OSVERSIONINFO WindowsVersion;
		WindowsVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&WindowsVersion);
		if (WindowsVersion.dwMajorVersion < 5 && WindowsVersion.dwMinorVersion >= 3)
		{
			MessageBox(NULL, Strings->OS_NOT_SUPPORTED, NULL, NULL);
			TerminateProcess(GetCurrentProcess(), 0);
		}

		while (!dwD3D9)
			dwD3D9 = (DWORD)GetModuleHandle(Strings->MODULE_D3D9);

		GetModuleInformation(GetCurrentProcess(), (HMODULE)dwD3D9, &mInfo, sizeof(MODULEINFO));

		if (WindowsVersion.dwMajorVersion == 6 && WindowsVersion.dwMinorVersion == 2)//Windows 8
		{
			dwDIP = (int)mInfo.EntryPoint + 0xFFFFFFFFFFFE95B7;
			dwEndScene = (int)mInfo.EntryPoint + 0xFFFFFFFFFFFDF736;
			dwReset = (int)mInfo.EntryPoint + 0xFFFFFFFFFFFF28E6;
		}
		else if (WindowsVersion.dwMajorVersion == 6 && WindowsVersion.dwMinorVersion == 1)//Windows 7  
		{
			dwEndScene = (int)mInfo.EntryPoint + 0x20D5A;
			dwDIP = (int)mInfo.EntryPoint + 0x29C6C;
			dwReset = (int)mInfo.EntryPoint + 0x5D80C;
		}
		else if (WindowsVersion.dwMajorVersion == 5 && WindowsVersion.dwMinorVersion == 1)//Windows XP
		{
			dwEndScene = (int)mInfo.EntryPoint + 0x7A2E;
			dwReset = (int)mInfo.EntryPoint + 0xFFFFFFFFFFFC3F2E;
		}

		if (pbDIP)
			pDIP = (tDIP)DetourFunction(PBYTE(dwDIP), pbDIP);

		if (pbEndscene)
			pEndscene = (tEndscene)DetourFunction(PBYTE(dwEndScene), pbEndscene);

		//if (pbReset)
			//pReset = (tReset)DetourFunction(PBYTE(dwReset), pbReset);
	}

	void cDirectx::RenderString(int x, int y, DWORD color, char* text)
	{
		Font->RenderString(x, y, color, text);
	}
}