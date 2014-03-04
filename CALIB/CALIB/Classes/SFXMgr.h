#ifndef _SFXMGR_
#define _SFXMGR_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>

class cCharacterFX
{
public:
	char	unk1[16];
	int*	Object;			//0x10
	char	unk2[44];
	int		IsPlayer;		//0x40
	char	unk3[40];
	unsigned char	Index;	//0x6C
	char unknown112[8]; //0x0070
	float fStartPitch; //0x0078  
	float fStartYaw; //0x007C  
	char unknown128[1224]; //0x0080
	BYTE unk1287; //0x0548  
	bool bIsDead; //0x0549  
	bool bSpawnSheild; //0x054A  
	BYTE unk5563; //0x054B  
	char unknown1356[12]; //0x054C
	int* hHitbox; //0x0558  
	char unknown1372[96]; //0x055C
	WORD wUnk; //0x05BC  
	WORD wHealth; //0x05BE  
	WORD wArmor; //0x05C0  
};

class cSFXList
{
public:
	unsigned long	unk0;
	unsigned long*	List;
	unsigned long	unk1;
	int				Num;
};

class cSFXMgr
{
public:
	cSFXList		SFXList[0x3B];
};

#endif