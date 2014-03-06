#ifndef _MENU_ // matypaty <3
#define _MENU_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include "../Directx/Directx.h"
#include "../Strings/Strings.h"

class Tab
{
public:
	char* Name;
	bool Active;
	int x;
	int y;
};

class Check
{
public:
	char* Parent;
	char* Name;
	bool Checked;
	int* Variable;
	int x;
	int y;
};

class Slider
{
public:
	char* Parent;
	char* Name;
	int MaxValue;
	int Value;
	int Limit;
	int* Variable;
	int x;
	int y;
	int pos;
	char** Array;
};

/************************************************************************/
/* MENU CLASS                                                           */
/************************************************************************/
class cMenu
{
public:
	//Class Arrays.
	Tab Tabs[100];
	Check Checks[1000];
	Slider Sliders[1000];

	//Menu Variables.
	int ITEM_CHAMS, ITEM_NOFOG, ITEM_CROSSHAIR;
	int ITEM_FLY, ITEM_HOVER, ITEM_INVISIBLE, ITEM_SUPERJUMP;

	///
	int TabCount, CheckCount, SliderCount;
	int Aimkey, RapidKey, WeaponKey;
	char* ActiveName;
	POINT Cur;
	bool ClickToggle, MenuOpen;
	int sizeoftab;
	int draging;
	int keysave;
	int lastdragged;
	float Pitch, Yaw;
	bool LockView;
	int Radius;
	int waitforkey;

	//Functions.
	cMenu();
	void DrawMenu();
	void MenuNavigation();
	void CreateTab(char* Text);
	void CreateCheck(char* Parent, char* Text, int* Variable);
	void CreateSlider(char* Parent, char* Text, int MaxValue, int* Variable, char** Array);
	void DrawTab(int index, int x, int y, int width);
	void DrawCheckBox(int index, int x, int y);
	void DrawSlider(int index, int x, int y);
	int MouseOver(int x, int y, int x2, int y2, int type);
	void SwitchTab(int index);
}; extern cMenu* Menu;

#endif