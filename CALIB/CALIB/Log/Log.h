#ifndef _LOG_
#define _LOG_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>	
#include <stdio.h>
#include <fstream>
using namespace std;

class cLog
{
private:
	ofstream ofile;

public:
	cLog(char* szFile, bool bDelete = false);
	void __cdecl log(const char *fmt, ...);
}; extern cLog* Log;

#endif