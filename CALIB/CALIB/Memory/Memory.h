#ifndef _MEMORY_
#define _MEMORY_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <Psapi.h>

#include "../Classes\GameClientShell.h"
#include "../Classes\PlayerMgr.h"
#include "../Classes\LTModel.h"

class cMemory
{
private:
public:
	MODULEINFO MODULE_D3D9, MODULE_CSHELL, MODULE_ENGINE, MODULE_CLIENTFX;

	DWORD ADDRESS_GAMESTATUS, ADDRESS_LTCLIENT, ADDRESS_GAMECLIENTSHELL, ADDRESS_WEAPONMGR, ADDRESS_FIREWEAPON, ADDRESS_AMMO, ADDRESS_GETPLAYERBYINDEX, 
		ADDRESS_GETLOCALPLAYER, ADDRESS_CLIENTINFOMGR, ADDRESS_LTCOMMON, ADDRESS_DRAWPRIM, ADDRESS_SENDTOSERVER, ADDRESS_SUPERBULLETS, ADDRESS_GETFONTHANDLE,
		ADDRESS_BUILDFONT, ADDRESS_FILLFONT, ADDRESS_FONTECX, ADDRESS_GRAVITY, ADDRESS_JUMPVEL, ADDRESS_PICKUPDISTANCE, ADDRESS_ESP1, ADDRESS_ESP2;

	cWeaponMgr* WeaponMgr;
	cGameClientShell* GameClientShell;
	cPlayerMgr* PlayerMgr;

	cMemory();
	~cMemory();

	bool Compare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD Scan(MODULEINFO* mInfo, BYTE* bMask, char* szMask);
	DWORD Scan(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask);
	DWORD Scan(MODULEINFO* mInfo, BYTE* bMask, char* szMask, int index);
}; extern cMemory* Memory;

#endif