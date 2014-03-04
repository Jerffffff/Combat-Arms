#pragma once

#define MC_ITEMY(index)	 (Y+(index*I_SPC)+T_SPC+5)
#define MC_ITEMY1(index) (Y+(index*I_SPC)+T_SPC+(FS_SPC*1)+10)
#define MC_ITEMY2(index) (Y+(index*I_SPC)+T_SPC+(FS_SPC*2)+15)
#define MC_ITEMY3(index) (Y+(index*I_SPC)+T_SPC+(FS_SPC*3)+20)

//____________________Mousefix prevents bugs____________________________\\

#define mousefix_L  if(GetAsyncKeyState(VK_LBUTTON)){GetAsyncKeyState(VK_RBUTTON);}
#define mousefix_R  if(GetAsyncKeyState(VK_RBUTTON)){GetAsyncKeyState(VK_LBUTTON);}

//____________________Define Colors here____________________________\\

#define Red         	D3DCOLOR_ARGB (255, 255,   0,   0 )    
#define Blue			D3DCOLOR_ARGB (255,   0,   0, 255 )
#define Green       	D3DCOLOR_ARGB (255,   0, 255,   10)    
#define LightBlue       D3DCOLOR_ARGB (255,  51, 255, 255 )      
#define Black       	D3DCOLOR_ARGB (130,   0,   0,   0 ) 
#define Gray       		D3DCOLOR_ARGB (255, 190, 190, 190 )
#define GrayT       	D3DCOLOR_ARGB (130, 190, 190, 190 )
#define GrayLighter     D3DCOLOR_ARGB (130, 130, 130, 130 )
#define White       	D3DCOLOR_ARGB (255, 255, 255, 255 )
#define TBlack      	D3DCOLOR_ARGB (180,   0,   0,   0 )  
#define LightOutline	D3DCOLOR_ARGB( 255, 136, 144, 129 )
#define DarkOutline		D3DCOLOR_ARGB( 255,  37,  48,  32 )

//____________________Menu Class____________________________\\

#include <d3dx9.h>

class cMenu{

public:
	LPD3DXFONT pFont;
	
	POINT mpos;
	
	void  DrawString(float x, float y, DWORD color, LPD3DXFONT g_pFont, const char *fmt, ...);
	bool  MouseIsOver(int x, int y, int w, int h);
	void  FillRGB( int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice);
	void  DrawBorder(int x, int y, int w, int h, int s, D3DCOLOR FillColor, D3DCOLOR Color, LPDIRECT3DDEVICE9 device);
	void  CheckBox(int x, int y, bool &val, const char* text, LPDIRECT3DDEVICE9 pDevice);
	void  CreateGUI(LPDIRECT3DDEVICE9 pDevice);
	void  InitializeMenu();
	void  MenuBG(LPDIRECT3DDEVICE9 pDevice);
	void  InitializeGUI(LPDIRECT3DDEVICE9 pDevice);

	//Privat Members
		int
		NO,
		X,Y,TitleX,
		Current,
		Width,
		I_OFS,S_OFS,G_OFS,
		I_SPC,T_SPC,FS_SPC,FB_SPC
	;
	bool
		Show,
		Init
	;

	struct sitem
	{
		char title[50];
		char state[50];
		int	 type;
		int  max;
		int  no;
		int	 *val;
	}
	items[50];
	enum I_TYPES
	{
		T_TEXT = 0,
		T_ITEM = 1,
		T_CAT  = 2
	};

};
extern cMenu Menu;

//____________________Item struct____________________________\\

struct Items
{
	bool	
		Aimbot,
		NameESP,
		Chams,
		Fog,
		Rapid,
		FPS,
		tab[35],
		hack1,
		hack2,
		hack3,
		hack4,
		hack5,
		hack6,
		hack7,
		hack8,
		x1,
		x2,
		x3,
		x4;
	int text;

};
extern Items item;
