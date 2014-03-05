#include "HWID.h"
#include "../Strings/Strings.h"

extern "C"
{
	cHWID* HWID;

	cHWID::cHWID()
	{
		sHWID = Get();
	}

	string cHWID::Get()
	{
		char data[4096];
		ZeroMemory(data, 4096);
		unsigned long  len = 4000;
		PIP_ADAPTER_INFO pinfo = (PIP_ADAPTER_INFO)data;
		char sbuf[20];
		string sret;

		DWORD ret = GetAdaptersInfo(pinfo, &len);
		if (ret != ERROR_SUCCESS)
			return string(/*NULL*/XorStr<0xB3, 5, 0xFA4DE0F4>("\xFD\xE1\xF9\xFA" + 0xFA4DE0F4).s);

		for (int k = 0; k < 5; k++) {
			sprintf(sbuf, /*%02X-*/XorStr<0xED, 6, 0x6E0543B0>("\xC8\xDE\xDD\xA8\xDC" + 0x6E0543B0).s, pinfo->Address[k]);
			sret += sbuf;
		}
		sprintf(sbuf, /*%02X*/XorStr<0x2D, 5, 0xE1F8C9CD>("\x08\x1E\x1D\x68" + 0xE1F8C9CD).s, pinfo->Address[5]);
		sret += sbuf;

		return(sret);
	}
}