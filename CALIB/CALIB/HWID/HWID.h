#ifndef _HWID_
#define _HWID_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <string>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")

using namespace std;

class cHWID
{
private:
	string Get();
public:
	cHWID();
	string sHWID;
}; extern cHWID* HWID;

#endif