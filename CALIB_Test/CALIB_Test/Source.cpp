#include "CALIB.h"
cBreakpoint* Breakpoint1 = NULL;

DWORD dwFireWeaponJMP;
__declspec(naked) void __stdcall vFireWeapon()
{
	static ILTMessage_Read* pMsg;
	__asm
	{
		PUSHAD;
		PUSHFD;
		MOV pMsg, EAX
	}

	if (pMsg->Size() > 900)
		pMsg = pMsg->SubMsg(0, 800);
	else
		pMsg = pMsg->SubMsg(0, 600);

	_asm
	{
		POPFD;
		POPAD;

		PUSH pMsg;
		JMP dwFireWeaponJMP;
	}
}

DWORD dwAmmoJMP;
__declspec(naked) void __stdcall vAmmo()
{
	__asm JMP dwAmmoJMP;
}

DWORD dwSuperBulletsJMP;
__declspec(naked) void __stdcall vSuperBullets()
{
	__asm JMP dwSuperBulletsJMP;
}

DWORD dwESPJMP;
__declspec(naked) void __stdcall vESP()
{
	__asm JMP dwESPJMP;
}

HRESULT WINAPI myDIP(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, int BaseVertexIndex, UINT MinIndex, UINT NumVerts, UINT StartIndex, UINT PrimCount)
{

	return Directx->pDIP(pDevice, Type, BaseVertexIndex, MinIndex, NumVerts, StartIndex, PrimCount);
}

HRESULT WINAPI myEndscene(LPDIRECT3DDEVICE9 pDevice)
{
	Directx->pDevice = pDevice;
	pDevice->GetViewport(&Directx->viewport);

	Directx->DrawCrosshair(25, 0xFFFF0000);

	return Directx->pEndscene(pDevice);
}

bool bSuperJump = false;
bool bHover = false;
bool bFly = false, bbFly = false;
DWORD _stdcall dwBreakpoint1Thread(LPVOID)
{
	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);

	Memory = new cMemory();
	Directx = new cDirectx();
	Directx->HookEndscene(PBYTE(&myEndscene));

	Log->log("ADDRESS_GETFONTHANDLE: 0x%X", Memory->ADDRESS_GETFONTHANDLE);
	Log->log("ADDRESS_BUILDFONT: 0x%X", Memory->ADDRESS_BUILDFONT);
	Log->log("ADDRESS_FILLFONT: 0x%X", Memory->ADDRESS_FILLFONT);
	Log->log("ADDRESS_FONTECX: 0x%X", Memory->ADDRESS_FONTECX);

	Breakpoint1 = new cBreakpoint();

	dwFireWeaponJMP = Memory->ADDRESS_FIREWEAPON + 1;
	Breakpoint1->SetBreakPoint1(Memory->ADDRESS_FIREWEAPON, DWORD(&vFireWeapon));

	dwAmmoJMP = Memory->ADDRESS_AMMO + 0xB;
	Breakpoint1->SetBreakPoint2(Memory->ADDRESS_AMMO, DWORD(&vAmmo));

	dwSuperBulletsJMP = Memory->ADDRESS_SUPERBULLETS + 3;
	Breakpoint1->SetBreakPoint3(Memory->ADDRESS_SUPERBULLETS, DWORD(&vSuperBullets));

	dwESPJMP = Memory->ADDRESS_ESP1 + 2;
	Breakpoint1->SetBreakPoint4(Memory->ADDRESS_ESP1, DWORD(&vESP));

	Breakpoint1->Enable();

	for (int i = 0; i < Memory->WeaponMgr->iWeaponCount; i++)
	{
		cWeaponInfo* wep = Memory->WeaponMgr->pWeaponInfo[i];

		if (!IsBadReadPtr(wep, 4))
		{
			wep->fTripleShotMaxCamRecoilPitch = 0;
			wep->fTripleShotBaseCamRecoilPitch = 0;
			wep->fBaseCamRecoilPitch = 0;
			wep->fBaseCamRecoilAccelPitch = 0;

			wep->fDuckPerturb = 0;
			wep->fMoveDuckPerturb = 0;
			wep->fPerturbIncSpeed = 0;
			wep->fPerturbDecSpeed = 0;
			wep->fZoomedPerturbIncSpeed = 0;
			wep->fZoomedPerturbDecSpeed = 0;
			wep->fTripleShotPerturbIncSpeed = 0;
			wep->fTripleShotPerturbDecSpeed = 0;
			wep->dwTripleShotMinPerturb = 0;
			wep->dwTripleShotMaxPerturb = 0;
			wep->dwMaxPerturb = 0;
			wep->dwMinPerturb = 0;
			wep->dwZoomedMaxPerturb = 0;
			wep->dwZoomedMinPerturb = 0;

			wep->dwRange = 999999999;
			wep->dwEffectRange = 999999999;

			wep->fZoomTime = 0;

			wep->fCameraSwayXFreq = 0;
			wep->fCameraSwayXFreq = 0;
		}
	}

	while (1)
	{
		*(float*)Memory->ADDRESS_PICKUPDISTANCE = 999999999.0f;

		if (GetAsyncKeyState(VK_LBUTTON) < 0)
			Memory->PlayerMgr->FireCurrentWeapon();

		if (GetAsyncKeyState(VK_SPACE) < 0 && bFly)
		{
			if (!bbFly)
			{
				*(float*)Memory->ADDRESS_GRAVITY = 750.0f;
				bbFly = true;
			}
		}
		else
		{
			if (bbFly)
			{
				*(float*)Memory->ADDRESS_GRAVITY = -1099.0f;
				bbFly = false;
			}
		}

		if (GetAsyncKeyState(VK_MENU))
		{
			if (!bHover)
			{
				*(float*)Memory->ADDRESS_GRAVITY = 0.0f;
				bHover = true;
			}
		}
		else
		{
			if (bHover)
			{
				*(float*)Memory->ADDRESS_GRAVITY = -1099.0f;
				bHover = false;
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
			bFly = !bFly;

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			bSuperJump = !bSuperJump;

			if (bSuperJump)
				*(float*)Memory->ADDRESS_JUMPVEL = *(float*)Memory->ADDRESS_JUMPVEL * 2.5f;
			else
				*(float*)Memory->ADDRESS_JUMPVEL = *(float*)Memory->ADDRESS_JUMPVEL / 2.5f;
		}

		Sleep(50);
	}

	return NULL;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Strings = new cStrings();
		Log = new cLog("C:\\log.txt");
		CreateThread(0, 0, dwBreakpoint1Thread, 0, 0, 0);
	}

	return true;
}