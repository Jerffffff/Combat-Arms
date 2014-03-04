#ifndef _FONT_
#define _FONT_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../../Memory/Memory.h"

class cEFont
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void SetSomthing(int a, int b, int c, int d);
	virtual void Function3();
	virtual void Render();
	virtual void Function5();
	virtual void Function6();
	virtual int GetX();
	virtual void SetPos(int x, int y);
	virtual void GetPos(int* x, int* y);
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual float GetScaleX();
	virtual float GetScaleY();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void SetColor(int c, int c_, int c__, int const_num);
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual void Function51();
	virtual void Function52();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void Function57();
	virtual void Function58();
	virtual void Function59();
	virtual void Function60();
	virtual void Function61();
	virtual void Function62();
	virtual void Function63();
	virtual void Function64();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual void Function68();
	virtual void Function69();
	virtual void Function70();
	virtual void Function71();
	virtual void Function72();
	virtual void Function73();
	virtual void Function74();
	virtual void Function75();
	virtual void Function76();
	virtual void Function77();
	virtual void Function78();
	virtual void Function79();
	virtual void Function80();
	virtual void Function81();
	virtual void Function82();
	virtual void Function83();
	virtual void SetText(unsigned short* text, int cont_num);
};

class cFont
{
private:
	cEFont* pFont;

	int GetFontHandle(int index);
	DWORD BuildFontByFontIndex(int index, int FontSize);
public:
	cFont();
	void RenderString(int x, int y, DWORD color, char* text);
};

#endif