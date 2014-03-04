#include "Log.h"

extern "C"
{
	cLog::cLog(char* szFile, bool bDelete)
	{
		if (bDelete)
			DeleteFile(szFile);
		ofile.open(szFile, ios::app);
	}

	void __cdecl cLog::log(const char *fmt, ...)
	{
		va_list va_alist;
		char logbuf[256] = { 0 };

		va_start(va_alist, fmt);
		_vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf)-strlen(logbuf), fmt, va_alist);
		va_end(va_alist);

		ofile << logbuf << endl;
	}
}