#include "Strings.h"

extern "C"
{
	cStrings* Strings;

	/*
	** Dynamically allocates and assigns a specific value to all of the strings.
	*/
	cStrings::cStrings()
	{
		szAssign = new char[3];
		sprintf(szAssign, /*%s*/XorStr<0x5F, 3, 0x01717FF1>("\x7A\x13" + 0x01717FF1).s, /*%s*/XorStr<0x5F, 3, 0x01717FF1>("\x7A\x13" + 0x01717FF1).s);

		Assign(&MODULE_D3D9, /*d3d9.dll*/XorStr<0x1E, 9, 0x74802921>("\x7A\x2C\x44\x18\x0C\x47\x48\x49" + 0x74802921).s);
		Assign(&MODULE_CSHELL, /*CShell.dll*/XorStr<0xAB, 11, 0x936CB208>("\xE8\xFF\xC5\xCB\xC3\xDC\x9F\xD6\xDF\xD8" + 0x936CB208).s);
		Assign(&MODULE_ENGINE, /*Engine.exe*/XorStr<0x0A, 11, 0x06EF1C82>("\x4F\x65\x6B\x64\x60\x6A\x3E\x74\x6A\x76" + 0x06EF1C82).s);
		Assign(&MODULE_CLIENTFX, /*ClientFX.fxd*/XorStr<0xDA, 13, 0xA91E763D>("\x99\xB7\xB5\xB8\xB0\xAB\xA6\xB9\xCC\x85\x9C\x81" + 0xA91E763D).s);

		Assign(&MASK_GAMESTATUS, /*xx????xxxxx*/XorStr<0xD5, 12, 0x3B199A44>("\xAD\xAE\xE8\xE7\xE6\xE5\xA3\xA4\xA5\xA6\xA7" + 0x3B199A44).s);
		Assign(&MASK_LTCLIENT, /*xx????xxxxx*/XorStr<0x32, 12, 0xAEC375A2>("\x4A\x4B\x0B\x0A\x09\x08\x40\x41\x42\x43\x44" + 0xAEC375A2).s);
		Assign(&MASK_GAMECLIENTSHELL, /*xx????xxxx????xxxx*/XorStr<0x3C, 19, 0x3B20198B>("\x44\x45\x01\x00\x7F\x7E\x3A\x3B\x3C\x3D\x79\x78\x77\x76\x32\x33\x34\x35" + 0x3B20198B).s);
		Assign(&MASK_WEAPONMGR, /*xx????xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/XorStr<0x5B, 51, 0x86E3AB27>("\x23\x24\x62\x61\x60\x5F\x19\x1A\x1B\x1C\x5A\x59\x58\x57\x11\x12\x13\x14\x15\x16\x17\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x00\x01\x02\x03\x04\x05\x06\x07\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF\xF0\xF1\xF2\xF3\xF4" + 0x86E3AB27).s);
		Assign(&MASK_FIREWEAPON, /*xxx????xxxxxxxxxxx*/XorStr<0x07, 19, 0x76AAC589>("\x7F\x70\x71\x35\x34\x33\x32\x76\x77\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F\x60" + 0x76AAC589).s);
		Assign(&MASK_AMMO, /*xxxxxxx*/XorStr<0x12, 8, 0x48A423AA>("\x6A\x6B\x6C\x6D\x6E\x6F\x60" + 0x48A423AA).s);
		Assign(&MASK_GETPLAYERBYINDEX, /*xxxxxxxxxxxxxxxx*/XorStr<0x68, 17, 0x119C96F7>("\x10\x11\x12\x13\x14\x15\x16\x17\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F" + 0x119C96F7).s);
		Assign(&MASK_GETLOCALPLAYER, /*xxxxxxxxxx*/XorStr<0xA2, 11, 0xB2613BE4>("\xDA\xDB\xDC\xDD\xDE\xDF\xD0\xD1\xD2\xD3" + 0xB2613BE4).s);
		Assign(&MASK_CLIENTINFOMGR, /*xx????xxxxxx????*/XorStr<0x71, 17, 0x3157B1C1>("\x09\x0A\x4C\x4B\x4A\x49\x0F\x00\x01\x02\x03\x04\x42\x41\x40\xBF" + 0x3157B1C1).s);
		Assign(&MASK_LTCOMMON, /*xx????xxxxx*/XorStr<0x71, 12, 0x6BDB35FD>("\x09\x0A\x4C\x4B\x4A\x49\x0F\x00\x01\x02\x03" + 0x6BDB35FD).s);
	}

	/*
	** Deletes the memory from all of the strings.
	*/
	cStrings::~cStrings()
	{
		delete[] szAssign;
		delete[] MODULE_D3D9;
		delete[] MODULE_CSHELL;
		delete[] MODULE_ENGINE;
		delete[] MODULE_CLIENTFX;
	}

	/*
	** Gives the corresponding variable the value of the given string.
	*/
	void cStrings::Assign(char** szVar, char* szBuf)
	{
		*szVar = new char[128];
		sprintf(*szVar, szAssign, szBuf);
	}
}