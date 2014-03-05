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

		/*
		** CShell.dll
		*/

		ADDRESS_GAMESTATUS = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x83\x79\x04\x00\x74", Strings->MASK_GAMESTATUS);
		ADDRESS_GAMESTATUS = (**(DWORD**)(ADDRESS_GAMESTATUS + 2)) - 4;

		ADDRESS_LTCLIENT = Scan(&MODULE_CSHELL, PBYTE("\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x50\x70"), Strings->MASK_LTCLIENT);
		ADDRESS_LTCLIENT = *(DWORD*)(ADDRESS_LTCLIENT + 2);
		LTClient = *(CLTClient**)ADDRESS_LTCLIENT;
		CommonLT = LTClient->Common();

		ADDRESS_GAMECLIENTSHELL = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x90\x00\x00\x00\x00\xFF\xD2\x8B\x10", Strings->MASK_GAMECLIENTSHELL);
		ADDRESS_GAMECLIENTSHELL = *(DWORD*)(ADDRESS_GAMECLIENTSHELL + 2);
		GameClientShell = *(cGameClientShell**)ADDRESS_GAMECLIENTSHELL;
		PlayerMgr = (cPlayerMgr*)GameClientShell->GetPlayerMgr();

		ADDRESS_WEAPONMGR = Scan(&MODULE_CSHELL, PBYTE("\x8B\x0D\x00\x00\x00\x00\x8B\xF8\x57\xE8\x00\x00\x00\x00\x0F\xB6\xC0\x83\xF8\x06\x77\x35\x8B\x4C\x24\x0C\x83\xF9\xFF\x75\x10\xC1\xE0\x07\x39\x7C\x30\x2C\x75\x23\x5F\xB0\x01\x5E\xC2\x04\x00\x83\xF9\x06"), Strings->MASK_WEAPONMGR);
		ADDRESS_WEAPONMGR = *(DWORD*)(ADDRESS_WEAPONMGR + 2);
		WeaponMgr = *(cWeaponMgr**)ADDRESS_WEAPONMGR;

		ADDRESS_FIREWEAPON = Scan(&MODULE_CSHELL, (PBYTE)"\x50\x8B\x82\x00\x00\x00\x00\xC6\x44\x24\x30\x01\xFF\xD0\x8B\x4C\x24\x38", Strings->MASK_FIREWEAPON);

		ADDRESS_AMMO = Scan(&MODULE_CSHELL, (PBYTE)"\x74\x09\x8B\x06\x8B\x50\x30", Strings->MASK_AMMO);

		ADDRESS_GETPLAYERBYINDEX = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x41\x04\x85\xC0\x74\x18\x8B\x54\x24\x04\xEB\x03\x8D\x49\x00", Strings->MASK_GETPLAYERBYINDEX);

		ADDRESS_GETLOCALPLAYER = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x41\x04\x8B\x51\x08\x85\xC0\x74\x15", Strings->MASK_GETLOCALPLAYER);

		ADDRESS_CLIENTINFOMGR = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\xC7\x6A\x00\x50\xE8\x00\x00\x00\x00", Strings->MASK_CLIENTINFOMGR);
		ADDRESS_CLIENTINFOMGR = *(DWORD*)(ADDRESS_CLIENTINFOMGR + 2);

		ADDRESS_LTCOMMON = Scan(&MODULE_CSHELL, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x50\x24", Strings->MASK_LTCOMMON);
		ADDRESS_LTCOMMON = *(DWORD*)(ADDRESS_LTCOMMON + 2);

		ADDRESS_SUPERBULLETS = Scan(&MODULE_CSHELL, PBYTE("\x0F\x94\xC0\x5E\xC3\xCC\xCC\xCC\xCC\xCC"), Strings->MASK_SUPERBULLETS);

		ADDRESS_GRAVITY = Scan(&MODULE_CSHELL, PBYTE("\xD9\x05\x00\x00\x00\x00\xDD\xE1\xDF\xE0\xDD\xD9\xF6\xC4\x44\x7A\x4C"), Strings->MASK_GRAVITY);
		ADDRESS_GRAVITY = *(DWORD*)(ADDRESS_GRAVITY + 2);

		ADDRESS_JUMPVEL = Scan(&MODULE_CSHELL, PBYTE("\xD9\x05\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\xD9\x5C\x24\x48"), Strings->MASK_JUMPVEL);
		ADDRESS_JUMPVEL = *(DWORD*)(ADDRESS_JUMPVEL + 2);

		ADDRESS_PICKUPDISTANCE = Scan(&MODULE_CSHELL, PBYTE("\xD9\x05\x00\x00\x00\x00\xEB\x02\xD9\xEE\xD9\x5C\x24\x04\xD9\x44\x24\x08"), Strings->MASK_PICKUPDISTANCE);
		ADDRESS_PICKUPDISTANCE = *(DWORD*)(ADDRESS_PICKUPDISTANCE + 2);

		ADDRESS_ESP1 = Scan(&MODULE_CSHELL, PBYTE("\x75\x05\xBD"), Strings->MASK_ESP);
		ADDRESS_ESP2 = Scan(ADDRESS_ESP1 + 1, MODULE_CSHELL.SizeOfImage, PBYTE("\x75\x05\xBD"), Strings->MASK_ESP);

		ADDRESS_GETFONTHANDLE = Scan(&MODULE_CSHELL, PBYTE("\x8B\x44\x24\x04\x56\x8B\xF1\x8B\x8E\x00\x00\x00\x00\x2B\x8E"), Strings->MASK_GETFONTHANDLE);
		ADDRESS_BUILDFONT = Scan(&MODULE_CSHELL, PBYTE("\x8B\x44\x24\x18\x56\x8B\xF1\x8B\x4C\x24\x14"), Strings->MASK_BUILDFONT);
		ADDRESS_FILLFONT = Scan(&MODULE_CSHELL, PBYTE("\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x51\x53\x55\x56\x57\xA1\x00\x00\x00\x00\x33\xC4\x50\x8D\x44\x24\x18\x64\xA3\x00\x00\x00\x00\x8B\xF1\x89\x74\x24\x14\xE8\x00\x00\x00\x00\x33\xFF"), Strings->MASK_FILLFONT);
		ADDRESS_FONTECX = Scan(&MODULE_CSHELL, PBYTE("\xA1\x00\x00\x00\x00\xD9\x80"), Strings->MASK_FONTECX);
		ADDRESS_FONTECX = *(DWORD*)(ADDRESS_FONTECX + 1);

		/*
		** Engine.exe
		*/

		ADDRESS_SENDTOSERVER = Scan(&MODULE_ENGINE, (PBYTE)"\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x2C", Strings->MASK_SENDTOSERVER);
		SendToServer = (tSendToServer)ADDRESS_SENDTOSERVER;

		///////fix
		//ADDRESS_DRAWPRIM = Scan(&MODULE_ENGINE, (PBYTE)"\x8B\x50\x00\x8B\x12\x56\x8B\x70\x00\x89\xC\x96\x8B\x48\x00\xFF\x1\x5E\x8B\x40\x00\xFF\x0\xC3\x8B\xC1\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1\x00", "xx?xxxxx?xxxxx?xxxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxx");
		//ADDRESS_DRAWPRIM = *(DWORD*)(ADDRESS_DRAWPRIM + 0x99);
	}

	void cMemory::GetUnicodeBytesFromChar(char curChar, BYTE *bOut)
	{
		if (!bOut) return;

		switch (curChar)
		{
		case ' ': bOut[0] = 0x80; bOut[1] = 0x00; break;
		case '0': bOut[0] = 0xC0; bOut[1] = 0x00; break;
		case '1': bOut[0] = 0xC4; bOut[1] = 0x00; break;
		case '2': bOut[0] = 0xC8; bOut[1] = 0x00; break;
		case '3': bOut[0] = 0xCC; bOut[1] = 0x00; break;
		case '4': bOut[0] = 0xD0; bOut[1] = 0x00; break;
		case '5': bOut[0] = 0xD4; bOut[1] = 0x00; break;
		case '6': bOut[0] = 0xD8; bOut[1] = 0x00; break;
		case '7': bOut[0] = 0xDC; bOut[1] = 0x00; break;
		case '8': bOut[0] = 0xE0; bOut[1] = 0x00; break;
		case '9': bOut[0] = 0xE4; bOut[1] = 0x00; break;

		case 'A': bOut[0] = 0x04; bOut[1] = 0x01; break;
		case 'B': bOut[0] = 0x08; bOut[1] = 0x01; break;
		case 'C': bOut[0] = 0x0C; bOut[1] = 0x01; break;
		case 'D': bOut[0] = 0x10; bOut[1] = 0x01; break;
		case 'E': bOut[0] = 0x14; bOut[1] = 0x01; break;
		case 'F': bOut[0] = 0x18; bOut[1] = 0x01; break;
		case 'G': bOut[0] = 0x1C; bOut[1] = 0x01; break;
		case 'H': bOut[0] = 0x20; bOut[1] = 0x01; break;
		case 'I': bOut[0] = 0x24; bOut[1] = 0x01; break;
		case 'J': bOut[0] = 0x28; bOut[1] = 0x01; break;
		case 'K': bOut[0] = 0x2C; bOut[1] = 0x01; break;
		case 'L': bOut[0] = 0x30; bOut[1] = 0x01; break;
		case 'M': bOut[0] = 0x34; bOut[1] = 0x01; break;
		case 'N': bOut[0] = 0x38; bOut[1] = 0x01; break;
		case 'O': bOut[0] = 0x3C; bOut[1] = 0x01; break;
		case 'P': bOut[0] = 0x40; bOut[1] = 0x01; break;
		case 'Q': bOut[0] = 0x44; bOut[1] = 0x01; break;
		case 'R': bOut[0] = 0x48; bOut[1] = 0x01; break;
		case 'S': bOut[0] = 0x4C; bOut[1] = 0x01; break;
		case 'T': bOut[0] = 0x50; bOut[1] = 0x01; break;
		case 'U': bOut[0] = 0x54; bOut[1] = 0x01; break;
		case 'V': bOut[0] = 0x58; bOut[1] = 0x01; break;
		case 'W': bOut[0] = 0x5C; bOut[1] = 0x01; break;
		case 'X': bOut[0] = 0x60; bOut[1] = 0x01; break;
		case 'Y': bOut[0] = 0x64; bOut[1] = 0x01; break;
		case 'Z': bOut[0] = 0x68; bOut[1] = 0x01; break;

		case 'a': bOut[0] = 0x84; bOut[1] = 0x01; break;
		case 'b': bOut[0] = 0x88; bOut[1] = 0x01; break;
		case 'c': bOut[0] = 0x8C; bOut[1] = 0x01; break;
		case 'd': bOut[0] = 0x90; bOut[1] = 0x01; break;
		case 'e': bOut[0] = 0x94; bOut[1] = 0x01; break;
		case 'f': bOut[0] = 0x98; bOut[1] = 0x01; break;
		case 'g': bOut[0] = 0x9C; bOut[1] = 0x01; break;
		case 'h': bOut[0] = 0xA0; bOut[1] = 0x01; break;
		case 'i': bOut[0] = 0xA4; bOut[1] = 0x01; break;
		case 'j': bOut[0] = 0xA8; bOut[1] = 0x01; break;
		case 'k': bOut[0] = 0xAC; bOut[1] = 0x01; break;
		case 'l': bOut[0] = 0xB0; bOut[1] = 0x01; break;
		case 'm': bOut[0] = 0xB4; bOut[1] = 0x01; break;
		case 'n': bOut[0] = 0xB8; bOut[1] = 0x01; break;
		case 'o': bOut[0] = 0xBC; bOut[1] = 0x01; break;
		case 'p': bOut[0] = 0xC0; bOut[1] = 0x01; break;
		case 'q': bOut[0] = 0xC4; bOut[1] = 0x01; break;
		case 'r': bOut[0] = 0xC8; bOut[1] = 0x01; break;
		case 's': bOut[0] = 0xCC; bOut[1] = 0x01; break;
		case 't': bOut[0] = 0xD0; bOut[1] = 0x01; break;
		case 'u': bOut[0] = 0xD4; bOut[1] = 0x01; break;
		case 'v': bOut[0] = 0xD8; bOut[1] = 0x01; break;
		case 'w': bOut[0] = 0xDC; bOut[1] = 0x01; break;
		case 'x': bOut[0] = 0xE0; bOut[1] = 0x01; break;
		case 'y': bOut[0] = 0xE4; bOut[1] = 0x01; break;
		case 'z': bOut[0] = 0xE8; bOut[1] = 0x01; break;

		case '}': bOut[0] = 0xF4; bOut[1] = 0x01; break;
		case '²': bOut[0] = 0xC8; bOut[1] = 0x02; break;
		case '³': bOut[0] = 0xCC; bOut[1] = 0x02; break;
		case '{': bOut[0] = 0xEC; bOut[1] = 0x01; break;
		case '[': bOut[0] = 0x6C; bOut[1] = 0x01; break;
		case ']': bOut[0] = 0x74; bOut[1] = 0x01; break;
		case '~': bOut[0] = 0xF8; bOut[1] = 0x01; break;
		case '\\': bOut[0] = 0x70; bOut[1] = 0x01; break;
		case '|': bOut[0] = 0xF0; bOut[1] = 0x01; break;
		case 'µ': bOut[0] = 0xD4; bOut[1] = 0x02; break;
		case '@': bOut[0] = 0x00; bOut[1] = 0x01; break;
		case '€': bOut[0] = 0x00; bOut[1] = 0x02; break;
		case '=': bOut[0] = 0xF4; bOut[1] = 0x00; break;
		case '!': bOut[0] = 0x84; bOut[1] = 0x00; break;
		case '"': bOut[0] = 0x88; bOut[1] = 0x00; break;
		case '§': bOut[0] = 0x9C; bOut[1] = 0x02; break;
		case '$': bOut[0] = 0x90; bOut[1] = 0x00; break;
		case '%': bOut[0] = 0x94; bOut[1] = 0x00; break;
		case '&': bOut[0] = 0x98; bOut[1] = 0x00; break;
		case '/': bOut[0] = 0xBC; bOut[1] = 0x00; break;
		case '(': bOut[0] = 0xA0; bOut[1] = 0x00; break;
		case ')': bOut[0] = 0xA4; bOut[1] = 0x00; break;
		case '*': bOut[0] = 0xA8; bOut[1] = 0x00; break;
		case ';': bOut[0] = 0xEC; bOut[1] = 0x00; break;
		case '_': bOut[0] = 0x7C; bOut[1] = 0x01; break;
		case ':': bOut[0] = 0xE8; bOut[1] = 0x00; break;
		case '\'': bOut[0] = 0x9C; bOut[1] = 0x00; break;
		case '?': bOut[0] = 0xFC; bOut[1] = 0x00; break;
		case '°': bOut[0] = 0xC0; bOut[1] = 0x02; break;
		case '`': bOut[0] = 0x80; bOut[1] = 0x01; break;
		case '>': bOut[0] = 0xF8; bOut[1] = 0x00; break;
		case '^': bOut[0] = 0x78; bOut[1] = 0x01; break;
		case '+': bOut[0] = 0xAC; bOut[1] = 0x00; break;
		case '-': bOut[0] = 0xB4; bOut[1] = 0x00; break;
		case ',': bOut[0] = 0xB0; bOut[1] = 0x00; break;
		case '.': bOut[0] = 0xB8; bOut[1] = 0x00; break;
		case '#': bOut[0] = 0x8C; bOut[1] = 0x00; break;
		case 'ß': bOut[0] = 0x7C; bOut[1] = 0x03; break;
		case '<': bOut[0] = 0xF0; bOut[1] = 0x00; break;

		default: bOut[0] = 0xFC; bOut[1] = 0x00; break;//'?' 
		}
	}

	void cMemory::ChatMessage(char *title, char *message)
	{
		//LTClient = *(CLTClient**)ADDRESS_LTCLIENT;
		//CommonLT = LTClient->Common();

		pMsg.Reset();
		pMsg.Writeuint8(104);

		for (int i = 0; i < (int)strlen(message); i++)
		{
			BYTE bChar[2] = { 0 };
			GetUnicodeBytesFromChar(message[i], bChar);
			pMsg.Writeuint8((BYTE)bChar[0]);
			pMsg.Writeuint8((BYTE)bChar[1]);
		}
		pMsg.Writeuint16(0);

		for (int i = 0; i < (int)strlen(title); i++)
		{
			BYTE bChar[2] = { 0 };
			GetUnicodeBytesFromChar(title[i], bChar);
			pMsg.Writeuint8((BYTE)bChar[0]);
			pMsg.Writeuint8((BYTE)bChar[1]);
		}
		pMsg.Writeuint16(0);
		pMsg.Writeint32(0);

		SendToServer(pMsg.Read(), MESSAGE_GUARANTEED);
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