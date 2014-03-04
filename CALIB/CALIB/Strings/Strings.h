#ifndef _STRINGS_
#define _STRINGS_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>

template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
private:
	XorStr();
public:
	char s[BUFLEN];

	XorStr(const char * xs);

	~XorStr()
	{
		for (int i = 0; i < BUFLEN; i++) s[i] = 0;
	}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART, BUFLEN, XREFKILLER>::XorStr(const char * xs)
{
	int xvalue = XORSTART;
	int i = 0;

	for (; i < (BUFLEN - 1); i++)
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}

	s[BUFLEN - 1] = 0;
}

class cStrings
{
private:
	void Assign(char** szVar, char* szBuf);

public:
	char* szAssign;
	char* MODULE_D3D9, *MODULE_CSHELL, *MODULE_ENGINE, *MODULE_CLIENTFX;
	char* MASK_GAMESTATUS, *MASK_LTCLIENT;

	cStrings();
	~cStrings();
}; extern cStrings* Strings;

#endif