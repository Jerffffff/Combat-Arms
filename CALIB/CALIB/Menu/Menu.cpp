#include "Menu.h"
#include "../Memory/Memory.h"

const D3DCOLOR Red = D3DCOLOR_ARGB(255, 255, 0, 0);
const D3DCOLOR Yellow = D3DCOLOR_ARGB(255, 255, 255, 0);
const D3DCOLOR Green = D3DCOLOR_ARGB(255, 0, 255, 0);
const D3DCOLOR Blue = D3DCOLOR_ARGB(255, 0, 0, 255);
const D3DCOLOR Purple = D3DCOLOR_ARGB(255, 102, 0, 153);
const D3DCOLOR Pink = D3DCOLOR_ARGB(255, 255, 20, 147);
const D3DCOLOR Orange = D3DCOLOR_ARGB(255, 255, 165, 0);
const D3DCOLOR YellowGreen = D3DCOLOR_ARGB(255, 154, 205, 50);
const D3DCOLOR LightGrey = D3DCOLOR_ARGB(255, 211, 211, 211);
const D3DCOLOR LightCyan = D3DCOLOR_ARGB(255, 122, 139, 139);
const D3DCOLOR Snow = D3DCOLOR_ARGB(255, 139, 137, 137);
const D3DCOLOR TransBlue = D3DCOLOR_ARGB(150, 0, 0, 255);
const D3DCOLOR TransBlack = D3DCOLOR_ARGB(150, 0, 0, 0);
const D3DCOLOR TransBlack2 = D3DCOLOR_ARGB(80, 0, 0, 0);
const D3DCOLOR AQUA = D3DCOLOR_ARGB(255, 54, 231, 255);
const D3DCOLOR White = D3DCOLOR_ARGB(255, 255, 255, 255);
const D3DCOLOR Black = D3DCOLOR_ARGB(255, 0, 0, 0);
const D3DCOLOR DGrey = D3DCOLOR_ARGB(255, 59, 55, 57);
const D3DCOLOR Grey = D3DCOLOR_ARGB(255, 84, 79, 81);
const D3DCOLOR Outline = D3DCOLOR_ARGB(255, 140, 140, 140);

extern "C"
{
	cMenu* Menu;
	/************************************************************************/
	/* INITIATE MENU (CREATE HACKS HERE)                                    */
	/************************************************************************/
	cMenu::cMenu()
	{
		char* aNumbers[] = { /*1*/XorStr<0xF8, 2, 0x8FF35086>("\xC9" + 0x8FF35086).s, /*2*/XorStr<0x2C, 2, 0x38B7A6D3>("\x1E" + 0x38B7A6D3).s, /*3*/XorStr<0xCB, 2, 0x19E48046>("\xF8" + 0x19E48046).s, /*4*/XorStr<0xC1, 2, 0xD8524854>("\xF5" + 0xD8524854).s, /*5*/XorStr<0x93, 2, 0x8528736E>("\xA6" + 0x8528736E).s, /*6*/XorStr<0x08, 2, 0xE5970E16>("\x3E" + 0xE5970E16).s, /*7*/XorStr<0xEC, 2, 0xA3E63283>("\xDB" + 0xA3E63283).s, /*8*/XorStr<0x86, 2, 0x479A6389>("\xBE" + 0x479A6389).s, /*9*/XorStr<0xDF, 2, 0x30AA092F>("\xE6" + 0x30AA092F).s, /*10*/XorStr<0x29, 3, 0x589B0CAA>("\x18\x1A" + 0x589B0CAA).s, /*11*/XorStr<0x82, 3, 0x51C8AFEB>("\xB3\xB2" + 0x51C8AFEB).s, /*12*/XorStr<0xAA, 3, 0x7482A96F>("\x9B\x99" + 0x7482A96F).s };

		ActiveName = NULL;

		CreateTab(Strings->TAB_VISUAL);
		CreateCheck(Strings->TAB_VISUAL, Strings->ITEM_CHAMS, &ITEM_CHAMS);
		CreateCheck(Strings->TAB_VISUAL, Strings->ITEM_NOFOG, &ITEM_NOFOG);
		CreateCheck(Strings->TAB_VISUAL, Strings->ITEM_CROSSHAIR, &ITEM_CROSSHAIR);

		CreateTab(Strings->TAB_PLAYER);
		CreateCheck(Strings->TAB_PLAYER, Strings->ITEM_FLY, &ITEM_FLY);
		CreateCheck(Strings->TAB_PLAYER, Strings->ITEM_HOVER, &ITEM_HOVER);
		CreateCheck(Strings->TAB_PLAYER, Strings->ITEM_INVISIBLE, &ITEM_INVISIBLE);
		CreateSlider(Strings->TAB_PLAYER, Strings->ITEM_SUPERJUMP, 10, &ITEM_SUPERJUMP, aNumbers);

		Tabs[0].Active = true;
	}

	/************************************************************************/
	/* DRAW MENU                                                            */
	/************************************************************************/
	void cMenu::DrawMenu()
	{
		if (!MenuOpen || *(int*)Memory->ADDRESS_GAMESTATUS == 3)
			return;

		Directx->g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE);
		Directx->g_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		Directx->g_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

		if (*(int*)Memory->ADDRESS_GAMESTATUS == 1)
		{
			if (!LockView)
			{
				Pitch = Memory->PlayerMgr->Pitch;
				Yaw = Memory->PlayerMgr->Yaw;
				LockView = true;
			}
			else
			{
				Memory->PlayerMgr->Pitch = Pitch;
				Memory->PlayerMgr->Yaw = Yaw;
			}
		}
		
		//Body Stuff.
		Directx->GradientRect(10, 10, 300, 20, Grey, DGrey, gr_orientation::vertical);
		Directx->DrawFilledRectangle(10, 30, 300, 280, DGrey);
		Directx->DrawNonFilledRectangle(10, 10, 300, 300, Outline);
		Directx->PrintText(100, 20, White, Strings->MENU_TITLE);

		//Tabs.
		sizeoftab = 291 / (TabCount);
		Directx->DrawNonFilledRectangle(15, 61, sizeoftab * TabCount, 243, Outline);
		for (int i = 0; i < TabCount; i++)
		{
			DrawTab(i, 15 + (i*sizeoftab), 41, sizeoftab);
		}

		//Checks.
		int d = 0;
		for (int i = 0; i < CheckCount; i++)
		{
			if (strcmp(ActiveName, Checks[i].Parent) == 0)
			{
				DrawCheckBox(i, 30, 70 + (d * 20));
				d++;
			}
		}

		//Sliders.
		d = 0;
		for (int i = 0; i < SliderCount; i++)
		{
			if (strcmp(ActiveName, Sliders[i].Parent) == 0)
			{
				DrawSlider(i, 150, 100 + (d * 40));
				d++;
			}
		}

		Directx->g_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}

	/************************************************************************/
	/* MENU NAVIGATION                                                      */
	/************************************************************************/
	void cMenu::MenuNavigation()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			MenuOpen = !MenuOpen;
			if (!MenuOpen)
				LockView = false;
		}

		GetCursorPos(&Cur);

		//Tabs.
		for (int i = 0; i < TabCount; i++)
		{
			if (MouseOver(Tabs[i].x, Tabs[i].y, Tabs[i].x + sizeoftab, Tabs[i].y + 20, 1) == 2)
				SwitchTab(i);

			if (Tabs[i].Active)
				ActiveName = Tabs[i].Name;
		}


		//Checks.
		for (int i = 0; i < CheckCount; i++)
		{

			if ((MouseOver(Checks[i].x - 5, Checks[i].y - 5, Checks[i].x + 15, Checks[i].y + 15, 1) == 1) && (strcmp(ActiveName, Checks[i].Parent) == 0))
			{
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					Checks[i].Checked = true;

				if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
					Checks[i].Checked = false;
			}

			if (Checks[i].Checked)
				*Checks[i].Variable = 1;
			else
				*Checks[i].Variable = 0;
		}


		//Sliders.
		for (int i = 0; i < SliderCount; i++)
		{
			if (((MouseOver(Sliders[i].x, Sliders[i].y - 3, Sliders[i].x + 120, Sliders[i].y + 6, 0) == 2)) && (strcmp(ActiveName, Sliders[i].Parent) == 0) && draging == -1)
			{
				draging = i;
			}

			if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000) && draging >= 0)
			{
				lastdragged = draging;
				draging = -1;
			}

			if (draging == i)
			{
				//Calculate value based on click position.
				int Value1 = (Cur.x - Sliders[i].x);
				float Value2 = ((float)Value1 / (float)110) * (float)Sliders[i].MaxValue;//*100

				if ((int)Value2 > Sliders[i].Limit)
					Value2 = (float)Sliders[i].Limit;

				if ((int)Value2 < 0)
					Value2 = 0.0f;


				Sliders[i].Value = (int)Value2;
				*Sliders[i].Variable = Sliders[i].Value;
			}
		}
	}

	/************************************************************************/
	/* CREATE TAB                                                           */
	/************************************************************************/
	void cMenu::CreateTab(char* Text)
	{
		Tabs[TabCount].Name = Text;
		Tabs[TabCount].Active = false;
		TabCount++;
	}

	/************************************************************************/
	/* CREATE CHECK                                                          */
	/************************************************************************/
	void cMenu::CreateCheck(char* Parent, char* Text, int* Variable)
	{

		Checks[CheckCount].Parent = Parent;
		Checks[CheckCount].Name = Text;
		Checks[CheckCount].Checked = false;
		Checks[CheckCount].Variable = Variable;
		CheckCount++;
	}

	/************************************************************************/
	/* CREATE SLIDER                                                        */
	/************************************************************************/
	void cMenu::CreateSlider(char* Parent, char* Text, int MaxValue, int* Variable, char** Array)
	{
		Sliders[SliderCount].Parent = Parent;
		Sliders[SliderCount].Name = Text;
		Sliders[SliderCount].MaxValue = MaxValue;
		Sliders[SliderCount].Variable = Variable;
		Sliders[SliderCount].Array = Array;
		Sliders[SliderCount].Limit = MaxValue;
		SliderCount++;
	}

	/************************************************************************/
	/* DRAW TAB                                                             */
	/************************************************************************/
	void cMenu::DrawTab(int index, int x, int y, int width)
	{
		Tabs[index].x = x;
		Tabs[index].y = y;

		if (Tabs[index].Active)
		{
			Directx->GradientRect(x, y, width, 20, Grey, DGrey, gr_orientation::vertical);
			Directx->DrawNonFilledRectangle(x, y, width, 20, Outline);
			Directx->DrawFilledRectangle(x + 1, y + 1, width - 1, 3, Red);
			Directx->DrawFilledRectangle(x + 1, y + 19, width - 1, 2, DGrey);
		}
		else
		{
			Directx->DrawFilledRectangle(x + 1, y + 19, width - 1, 2, DGrey);
			Directx->DrawNonFilledRectangle(x, y, width, 20, Outline);
		}

		Directx->PrintText(x + 10, y + 5, White, Tabs[index].Name);
	}

	/************************************************************************/
	/* DRAW CHECKBOX                                                        */
	/************************************************************************/
	void cMenu::DrawCheckBox(int index, int x, int y)
	{
		Checks[index].x = x;
		Checks[index].y = y;
		Directx->DrawNonFilledRectangle(x, y, 10, 10, Outline);
		Directx->PrintText(x + 22, y, White, Checks[index].Name);

		if (Checks[index].Checked)
			Directx->DrawFilledRectangle(x + 1, y + 1, 9, 9, Red);
	}

	/************************************************************************/
	/* DRAW SLIDER                                                          */
	/************************************************************************/
	void cMenu::DrawSlider(int index, int x, int y)
	{
		Sliders[index].x = x;
		Sliders[index].y = y;
		Directx->DrawLine(x, y, x + 120, y, Outline);
		Directx->PrintText(x + 5, y - 15, White, Sliders[index].Name);
		char lol[256];

		if (Sliders[index].Array == NULL)
		{
			sprintf(lol, Strings->szAssign, Sliders[index].Value);
			Directx->PrintText(x + 55, y + 5, White, lol);
		}
		else
		{
			Directx->PrintText(x + 55, y + 5, White, Sliders[index].Array[Sliders[index].Value]);
		}

		//Actual Slider
		float fpos = ((float)Sliders[index].Value / (float)Sliders[index].MaxValue)*((float)120);
		float pos = (float)x + (float)fpos;
		Sliders[index].pos = (int)pos;

		Directx->DrawFilledRectangle(Sliders[index].pos - 10, y - 3, 20, 5, Grey);
		Directx->DrawNonFilledRectangle(Sliders[index].pos - 10, y - 3, 20, 5, White);
	}

	/************************************************************************/
	/* MOUSE OVER                                                           */
	/************************************************************************/
	int cMenu::MouseOver(int x, int y, int x2, int y2, int type)
	{
		if (Cur.x > x && Cur.x < x2 && Cur.y > y && Cur.y < y2)
		{
			if (type == 1)
			{
				if (GetAsyncKeyState(VK_LBUTTON) & 1)
					return 2;
			}
			else
			{
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					return 2;
			}

			return 1;
		}
		return 0;
	}

	/************************************************************************/
	/* SWITCH TAB                                                           */
	/************************************************************************/
	void cMenu::SwitchTab(int index)
	{
		for (int i = 0; i < TabCount; i++)
		{
			if (i == index)
				Tabs[i].Active = true;
			else
				Tabs[i].Active = false;
		}
	}
}