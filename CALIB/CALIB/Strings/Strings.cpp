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
		*szVar = new char[64];
		sprintf(*szVar, szAssign, szBuf);
	}
}