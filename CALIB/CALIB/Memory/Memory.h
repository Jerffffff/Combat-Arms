#ifndef _MEMORY_
#define _MEMORY_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <Psapi.h>

class cMemory
{
private:
public:
	MODULEINFO MODULE_D3D9, MODULE_CSHELL, MODULE_ENGINE, MODULE_CLIENTFX;
	DWORD ADDRESS_GAMESTATUS, ADDRESS_LTCLIENT, ADDRESS_GAMECLIENTSHELL, ADDRESS_WEAPONMGR, ADDRESS_FIREWEAPON, ADDRESS_AMMO;

	cMemory();
	~cMemory();

	bool Compare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD Scan(MODULEINFO* mInfo, BYTE* bMask, char* szMask);
	DWORD Scan(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask);
	DWORD Scan(MODULEINFO* mInfo, BYTE* bMask, char* szMask, int index);
}; extern cMemory* Memory;

#endif