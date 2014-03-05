#include "Menu.h"

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
	cMenu* menu = NULL;
	/************************************************************************/
	/* INITIATE MENU (CREATE HACKS HERE)                                    */
	/************************************************************************/
	void cMenu::InitMenu()
	{
		CreateTab(Strings->MENU_VISUAL);
		CreateCheck(Strings->MENU_VISUAL, Strings->ITEM_CHAMS, &ITEM_CHAMS);


		Tabs[0].Active = true;
	}

	/************************************************************************/
	/* DRAW MENU                                                            */
	/************************************************************************/
	void cMenu::DrawMenu()
	{
		/*
		#ifdef CA
		cPlayerMgr*			pPlayerManager;
		pPlayerManager      = *(cPlayerMgr**)ADDR_PLAYERMANAGER;

		//Freeze mouse
		if( !LockView )
		{
		Pitch =  pPlayerManager->Pitch;
		Yaw = pPlayerManager->Yaw;

		LockView = true;
		}

		pPlayerManager->Pitch = Pitch;
		pPlayerManager->Yaw = Yaw;
		#endif
		*/

		//Body Stuff.
		Directx->GradientRect(10, 10, 300, 20, Grey, DGrey, gr_orientation::vertical);
		Directx->DrawFilledRectangle(10, 30, 300, 280, DGrey);
		Directx->DrawNonFilledRectangle(10, 10, 300, 300, Outline);
		Directx->PrintText(100, 20, White, "amzer");

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
	}

	/************************************************************************/
	/* MENU NAVIGATION                                                      */
	/************************************************************************/
	void cMenu::MenuNavigation()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
			MenuOpen = !MenuOpen;

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