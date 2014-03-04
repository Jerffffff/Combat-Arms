#include "Memory.h"
#include "../Strings/Strings.h"

extern "C"
{
	cMemory* Memory;

	/*
	** Assign all of the 32bit variables declared in the header file using a specific signature scan for each address.
	** NOTE: Best used AFTER the module 'ClientFX.fxd' is loaded into memory.
	*/
	cMemory::cMemory()
	{
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(Strings->MODULE_D3D9), &MODULE_D3D9, sizeof(MODULEINFO));
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(Strings->MODULE_CSHELL), &MODULE_CSHELL, sizeof(MODULEINFO));
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(Strings->MODULE_ENGINE), &MODULE_ENGINE, sizeof(MODULEINFO));
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(Strings->MODULE_CLIENTFX), &MODULE_CLIENTFX, sizeof(MODULEINFO));

		ADDRESS_GAMESTATUS = scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x83\x79\x04\x00\x74", Strings->MASK_GAMESTATUS);
		ADDRESS_GAMESTATUS = (**(DWORD**)(ADDRESS_GAMESTATUS + 2)) - 4;

		ADDRESS_LTCLIENT = scan(&MODULE_CSHELL, PBYTE("\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x50\x70"), Strings->MASK_LTCLIENT);
		ADDRESS_LTCLIENT = *(DWORD*)(ADDRESS_LTCLIENT + 2);

		ADDRESS_GAMECLIENTSHELL = scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x90\x00\x00\x00\x00\xFF\xD2\x8B\xD8\x85\xDB\x0F\x84\x00\x00\x00\x00\x8B\x86\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x50\x33\xFF", Strings->MASK_GAMECLIENTSHELL);
		ADDRESS_GAMECLIENTSHELL = *(DWORD*)(ADDRESS_GAMECLIENTSHELL + 2);
	}

	bool cMemory::compare(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;

		return (*szMask) == NULL;
	}

	DWORD cMemory::scan(MODULEINFO* mInfo, BYTE *bMask, char * szMask)
	{
		for (DWORD i = 0; i < mInfo->SizeOfImage; i++)
		if (compare((BYTE*)((DWORD)mInfo->lpBaseOfDll + i), bMask, szMask))
			return (DWORD)((DWORD)mInfo->lpBaseOfDll + i);
		return 0;
	}
}