#include "Memory.h"
#include "../Strings/Strings.h"
#include "../Log/Log.h"

extern "C"
{
	CCommonLT* CommonLT;
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

		/*
		** CShell.dll
		*/

		ADDRESS_GAMESTATUS = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x83\x79\x04\x00\x74", Strings->MASK_GAMESTATUS);
		ADDRESS_GAMESTATUS = (**(DWORD**)(ADDRESS_GAMESTATUS + 2)) - 4;
		//Log->log("ADDRESS_GAMESTATUS: 0x%X", ADDRESS_GAMESTATUS);

		ADDRESS_LTCLIENT = Scan(&MODULE_CSHELL, PBYTE("\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x50\x70"), Strings->MASK_LTCLIENT);
		ADDRESS_LTCLIENT = *(DWORD*)(ADDRESS_LTCLIENT + 2);
		//Log->log("ADDRESS_LTCLIENT: 0x%X", ADDRESS_LTCLIENT);
		LTClient = *(CLTClient**)ADDRESS_LTCLIENT;
		CommonLT = LTClient->Common();

		ADDRESS_GAMECLIENTSHELL = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x90\x00\x00\x00\x00\xFF\xD2\x8B\x10", Strings->MASK_GAMECLIENTSHELL);
		ADDRESS_GAMECLIENTSHELL = *(DWORD*)(ADDRESS_GAMECLIENTSHELL + 2);
		//Log->log("ADDRESS_GAMECLIENTSHELL: 0x%X", ADDRESS_GAMECLIENTSHELL);
		GameClientShell = *(cGameClientShell**)ADDRESS_GAMECLIENTSHELL;
		PlayerMgr = (cPlayerMgr*)GameClientShell->GetPlayerMgr();

		ADDRESS_WEAPONMGR = Scan(&MODULE_CSHELL, PBYTE("\x8B\x0D\x00\x00\x00\x00\x8B\xF8\x57\xE8\x00\x00\x00\x00\x0F\xB6\xC0\x83\xF8\x06\x77\x35\x8B\x4C\x24\x0C\x83\xF9\xFF\x75\x10\xC1\xE0\x07\x39\x7C\x30\x2C\x75\x23\x5F\xB0\x01\x5E\xC2\x04\x00\x83\xF9\x06"), Strings->MASK_WEAPONMGR);
		ADDRESS_WEAPONMGR = *(DWORD*)(ADDRESS_WEAPONMGR + 2);
		//Log->log("ADDRESS_WEAPONMGR: 0x%X", ADDRESS_WEAPONMGR);
		WeaponMgr = *(cWeaponMgr**)ADDRESS_WEAPONMGR;

		ADDRESS_FIREWEAPON = Scan(&MODULE_CSHELL, (PBYTE)"\x50\x8B\x82\x00\x00\x00\x00\xC6\x44\x24\x30\x01\xFF\xD0\x8B\x4C\x24\x38", Strings->MASK_FIREWEAPON);
		//Log->log("ADDRESS_FIREWEAPON: 0x%X", ADDRESS_FIREWEAPON);

		ADDRESS_AMMO = Scan(&MODULE_CSHELL, (PBYTE)"\x74\x09\x8B\x06\x8B\x50\x30", Strings->MASK_AMMO);
		//Log->log("ADDRESS_AMMO: 0x%X", ADDRESS_AMMO);

		ADDRESS_GETPLAYERBYINDEX = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x41\x04\x85\xC0\x74\x18\x8B\x54\x24\x04\xEB\x03\x8D\x49\x00", Strings->MASK_GETPLAYERBYINDEX);
		//Log->log("ADDRESS_GETPLAYERBYINDEX: 0x%X", ADDRESS_GETPLAYERBYINDEX);

		ADDRESS_GETLOCALPLAYER = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x41\x04\x8B\x51\x08\x85\xC0\x74\x15", Strings->MASK_GETLOCALPLAYER);
		//Log->log("ADDRESS_GETLOCALPLAYER: 0x%X", ADDRESS_GETLOCALPLAYER);

		ADDRESS_CLIENTINFOMGR = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\xC7\x6A\x00\x50\xE8\x00\x00\x00\x00", Strings->MASK_CLIENTINFOMGR);
		ADDRESS_CLIENTINFOMGR = *(DWORD*)(ADDRESS_CLIENTINFOMGR + 2);
		//Log->log("ADDRESS_CLIENTINFOMGR: 0x%X", ADDRESS_CLIENTINFOMGR);

		ADDRESS_LTCOMMON = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x50\x24", Strings->MASK_LTCOMMON);
		ADDRESS_LTCOMMON = *(DWORD*)(ADDRESS_LTCOMMON + 2);
		//Log->log("ADDRESS_LTCOMMON: 0x%X", ADDRESS_LTCOMMON);

		ADDRESS_SUPERBULLETS = Scan(&MODULE_CSHELL, PBYTE("\x0F\x94\xC0\x5E\xC3\xCC\xCC\xCC\xCC\xCC"), Strings->MASK_SUPERBULLETS);
		//Log->log("ADDRESS_SUPERBULLETS: 0x%X", ADDRESS_SUPERBULLETS);

		ADDRESS_GRAVITY = Scan(&MODULE_CSHELL, PBYTE("\xD9\x05\x00\x00\x00\x00\xDD\xE1\xDF\xE0\xDD\xD9\xF6\xC4\x44\x7A\x4C"), Strings->MASK_GRAVITY);
		ADDRESS_GRAVITY = *(DWORD*)(ADDRESS_GRAVITY + 2);
		//Log->log("ADDRESS_GRAVITY: 0x%X", ADDRESS_GRAVITY);

		ADDRESS_JUMPVEL = Scan(&MODULE_CSHELL, PBYTE("\xD9\x05\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\xD9\x5C\x24\x48"), Strings->MASK_JUMPVEL);
		ADDRESS_JUMPVEL = *(DWORD*)(ADDRESS_JUMPVEL + 2);
		//Log->log("ADDRESS_JUMPVEL: 0x%X", ADDRESS_JUMPVEL);

		ADDRESS_PICKUPDISTANCE = Scan(&MODULE_CSHELL, PBYTE("\xD9\x05\x00\x00\x00\x00\xEB\x02\xD9\xEE\xD9\x5C\x24\x04\xD9\x44\x24\x08"), Strings->MASK_PICKUPDISTANCE);
		ADDRESS_PICKUPDISTANCE = *(DWORD*)(ADDRESS_PICKUPDISTANCE + 2);
		//Log->log("ADDRESS_PICKUPDISTANCE: 0x%X", ADDRESS_PICKUPDISTANCE);

		ADDRESS_ESP1 = Scan(&MODULE_CSHELL, PBYTE("\x75\x05\xBD"), Strings->MASK_ESP);
		//Log->log("ADDRESS_ESP1: 0x%X", ADDRESS_ESP1);
		ADDRESS_ESP2 = Scan(ADDRESS_ESP1 + 1, MODULE_CSHELL.SizeOfImage, PBYTE("\x75\x05\xBD"), Strings->MASK_ESP);
		//Log->log("ADDRESS_ESP2: 0x%X", ADDRESS_ESP2);

		ADDRESS_GETFONTHANDLE = Scan(&MODULE_CSHELL, PBYTE("\x8B\x44\x24\x04\x56\x8B\xF1\x8B\x8E\x00\x00\x00\x00\x2B\x8E"), Strings->MASK_GETFONTHANDLE);
		//Log->log("ADDRESS_GETFONTHANDLE: 0x%X", ADDRESS_GETFONTHANDLE);
		ADDRESS_BUILDFONT = Scan(&MODULE_CSHELL, PBYTE("\x8B\x44\x24\x18\x56\x8B\xF1\x8B\x4C\x24\x14"), Strings->MASK_BUILDFONT);
		//Log->log("ADDRESS_BUILDFONT: 0x%X", ADDRESS_BUILDFONT);
		ADDRESS_FILLFONT = Scan(&MODULE_CSHELL, PBYTE("\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x51\x53\x55\x56\x57\xA1\x00\x00\x00\x00\x33\xC4\x50\x8D\x44\x24\x18\x64\xA3\x00\x00\x00\x00\x8B\xF1\x89\x74\x24\x14\xE8\x00\x00\x00\x00\x33\xFF"), Strings->MASK_FILLFONT);
		//Log->log("ADDRESS_FILLFONT: 0x%X", ADDRESS_FILLFONT);
		ADDRESS_FONTECX = Scan(&MODULE_CSHELL, PBYTE("\xA1\x00\x00\x00\x00\xD9\x80"), Strings->MASK_FONTECX);
		ADDRESS_FONTECX = *(DWORD*)(ADDRESS_FONTECX + 1);
		//Log->log("ADDRESS_FONTECX: 0x%X", ADDRESS_FONTECX);

		/*
		** Engine.exe
		*/

		ADDRESS_SENDTOSERVER = Scan(&MODULE_ENGINE, (PBYTE)"\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x2C", Strings->MASK_SENDTOSERVER);
		//Log->log("ADDRESS_SENDTOSERVER: 0x%X", ADDRESS_SENDTOSERVER);
		SendToServer = (tSendToServer)ADDRESS_SENDTOSERVER;

		///////fix
		//ADDRESS_DRAWPRIM = Scan(&MODULE_ENGINE, (PBYTE)"\x8B\x50\x00\x8B\x12\x56\x8B\x70\x00\x89\xC\x96\x8B\x48\x00\xFF\x1\x5E\x8B\x40\x00\xFF\x0\xC3\x8B\xC1\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00", "xx?xxxxx?xxxxx?xxxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx");
		//ADDRESS_DRAWPRIM = *(DWORD*)(ADDRESS_DRAWPRIM + 0x99);
	}

	const wchar_t* cMemory::pchar2pwchar(const char* indata)
	{
		std::string UTF8String;
		static std::wstring UTF16String;
		UTF8String = indata;
		UTF16String.resize(UTF8String.length());
		std::copy(UTF8String.begin(), UTF8String.end(), UTF16String.begin());
		return UTF16String.c_str();
	}

	void cMemory::Respawn()
	{
		CAutoMessage Msg;
		Msg.Writeuint8(113);
		Msg.Writeuint8(1);
		Msg.Writeuint32(1);
		SendToServer(Msg.Read(), MESSAGE_GUARANTEED);
	}

	void cMemory::ChatMessage(char *title, char *message)
	{
		CAutoMessage Msg;
		Msg.Writeuint8(104);
		Msg.WriteWString(pchar2pwchar(message));
		Msg.WriteWString(pchar2pwchar(title));
		Msg.Writeuint16(0);
		Msg.Writeint32(0);
		SendToServer(Msg.Read(), MESSAGE_GUARANTEED);
	}

	bool cMemory::Compare(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;

		return (*szMask) == NULL;
	}

	DWORD cMemory::Scan(MODULEINFO* mInfo, BYTE* bMask, char* szMask)
	{
		for (DWORD i = 0; i < mInfo->SizeOfImage; i++)
		if (Compare((BYTE*)((DWORD)mInfo->lpBaseOfDll + i), bMask, szMask))
			return (DWORD)((DWORD)mInfo->lpBaseOfDll + i);
		return NULL;
	}

	DWORD cMemory::Scan(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask)
	{
		for (DWORD i = 0; i < dwLen; i++)
		if (Compare((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);
		return NULL;
	}

	DWORD cMemory::Scan(MODULEINFO* pInfo, BYTE* bMask, char* szMask, int index)
	{
		DWORD ret = NULL;
		DWORD dwAddress = (DWORD)pInfo->lpBaseOfDll;
		for (int i = 0; i <= index;)
		{
			ret = Scan(dwAddress, pInfo->SizeOfImage, bMask, szMask);
			if (ret)
			{
				dwAddress = ret + 1;
				++i;
			}
			else break;
		}

		return ret;
	}
}