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

		ADDRESS_WEAPONMGR = scan(&MODULE_CSHELL, PBYTE("\x8B\x0D\x00\x00\x00\x00\x8B\xF8\x57\xE8\x00\x00\x00\x00\x0F\xB6\xC0\x83\xF8\x06\x77\x35\x8B\x4C\x24\x0C\x83\xF9\xFF\x75\x10\xC1\xE0\x07\x39\x7C\x30\x2C\x75\x23\x5F\xB0\x01\x5E\xC2\x04\x00\x83\xF9\x06"), Strings->MASK_WEAPONMGR);
		ADDRESS_WEAPONMGR = *(DWORD*)(ADDRESS_WEAPONMGR + 2);

		ADDRESS_FIREWEAPON = scan(&MODULE_CSHELL, (PBYTE)"\x50\x8B\x82\x00\x00\x00\x00\xC6\x44\x24\x30\x01\xFF\xD0\x8B\x4C\x24\x38", Strings->MASK_FIREWEAPON);

		ADDRESS_AMMO = scan(&MODULE_CSHELL, (PBYTE)"\x74\x09\x8B\x06\x8B\x50\x30", Strings->MASK_AMMO);
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