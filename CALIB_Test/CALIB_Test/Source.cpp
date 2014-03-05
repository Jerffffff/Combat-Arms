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

bool bChams = false;
#define smPlayer (Directx->Stride == 44) 
#define smHeads (Directx->Stride == 36) 
#define smGuns (Directx->Stride == 32) 
#define Hands (Directx->Stride == 40 && NumVerts == 18 && PrimCount == 11) 
#define SpecialistViper ( Directx->Stride == 40 && NumVerts == 647 && PrimCount == 826 ) || ( Directx->Stride == 40 && NumVerts == 37 && PrimCount == 40 ) || ( Directx->Stride == 40 && NumVerts == 24 && PrimCount == 24 ) || ( Directx->Stride == 32 && NumVerts == 12 && PrimCount == 12 ) || ( Directx->Stride == 32 && NumVerts == 104 && PrimCount == 118 ) || ( Directx->Stride == 40 && NumVerts == 73 && PrimCount == 48 ) || ( Directx->Stride == 40 && NumVerts == 252 && PrimCount == 205 ) || ( Directx->Stride == 40 && NumVerts == 92 && PrimCount == 64 ) || ( Directx->Stride == 40 && NumVerts == 37 && PrimCount == 25 ) || ( Directx->Stride == 40 && NumVerts == 92 && PrimCount == 69 ) || ( Directx->Stride == 40 && NumVerts == 126 && PrimCount == 68 ) || ( Directx->Stride == 40 && NumVerts == 101 && PrimCount == 72 ) || ( Directx->Stride == 40 && NumVerts == 70 && PrimCount == 36 ) || ( Directx->Stride == 40 && NumVerts == 6 && PrimCount == 2 ) || ( Directx->Stride == 40 && NumVerts == 8 && PrimCount == 3 ) || ( Directx->Stride == 40 && NumVerts == 82 && PrimCount == 105 ) || ( Directx->Stride == 40 && NumVerts == 168 && PrimCount == 173 ) || ( Directx->Stride == 40 && NumVerts == 87 && PrimCount == 67 ) || ( Directx->Stride == 40 && NumVerts == 37 && PrimCount == 26 ) || ( Directx->Stride == 40 && NumVerts == 10 && PrimCount == 11 ) || ( Directx->Stride == 40 && NumVerts == 25 && PrimCount == 17 ) || ( Directx->Stride == 40 && NumVerts == 15 && PrimCount == 8 ) || ( Directx->Stride == 40 && NumVerts == 16 && PrimCount == 10 ) || ( Directx->Stride == 40 && NumVerts == 26 && PrimCount == 19 ) || ( Directx->Stride == 40 && NumVerts == 12 && PrimCount == 4 ) || ( Directx->Stride == 40 && NumVerts == 21 && PrimCount == 15 ) || ( Directx->Stride == 40 && NumVerts == 15 && PrimCount == 9 ) || ( Directx->Stride == 40 && NumVerts == 10 && PrimCount == 6 ) || ( Directx->Stride == 40 && NumVerts == 7 && PrimCount == 3 ) || ( Directx->Stride == 40 && NumVerts == 134 && PrimCount == 108 ) || ( Directx->Stride == 40 && NumVerts == 226 && PrimCount == 217 ) || ( Directx->Stride == 40 && NumVerts == 51 && PrimCount == 52 ) || ( Directx->Stride == 40 && NumVerts == 34 && PrimCount == 32 ) || ( Directx->Stride == 40 && NumVerts == 21 && PrimCount == 25 ) || ( Directx->Stride == 40 && NumVerts == 12 && PrimCount == 8 ) || ( Directx->Stride == 40 && NumVerts == 99 && PrimCount == 135 ) || ( Directx->Stride == 40 && NumVerts == 36 && PrimCount == 36 ) || ( Directx->Stride == 32 && NumVerts == 1182 && PrimCount == 731 ) || ( Directx->Stride == 32 && NumVerts == 17 && PrimCount == 14 ) 
#define SpecialistScorpion ( Directx->Stride == 32 && NumVerts == 1182 && PrimCount == 731 ) || ( Directx->Stride == 32 && NumVerts == 91 && PrimCount == 134 ) || ( Directx->Stride == 32 && NumVerts == 10 && PrimCount == 9 ) || ( Directx->Stride == 32 && NumVerts == 17 && PrimCount == 14 ) || ( Directx->Stride == 40 && NumVerts == 295 && PrimCount == 171 ) || ( Directx->Stride == 40 && NumVerts == 133 && PrimCount == 162 ) || ( Directx->Stride == 40 && NumVerts == 166 && PrimCount == 198 ) || ( Directx->Stride == 40 && NumVerts == 203 && PrimCount == 227 ) || ( Directx->Stride == 40 && NumVerts == 81 && PrimCount == 72 ) || ( Directx->Stride == 40 && NumVerts == 60 && PrimCount == 62 ) || ( Directx->Stride == 40 && NumVerts == 10 && PrimCount == 8 ) || ( Directx->Stride == 40 && NumVerts == 17 && PrimCount == 10 ) || ( Directx->Stride == 40 && NumVerts == 210 && PrimCount == 386 ) || ( Directx->Stride == 44 && NumVerts == 244 && PrimCount == 176 ) || ( Directx->Stride == 44 && NumVerts == 323 && PrimCount == 340 ) || ( Directx->Stride == 44 && NumVerts == 181 && PrimCount == 166 ) || ( Directx->Stride == 44 && NumVerts == 8 && PrimCount == 6 ) || ( Directx->Stride == 44 && NumVerts == 153 && PrimCount == 133 ) || ( Directx->Stride == 44 && NumVerts == 111 && PrimCount == 117 ) || ( Directx->Stride == 44 && NumVerts == 4 && PrimCount == 2 ) || ( Directx->Stride == 44 && NumVerts == 214 && PrimCount == 184 ) || ( Directx->Stride == 44 && NumVerts == 31 && PrimCount == 18 ) || ( Directx->Stride == 44 && NumVerts == 51 && PrimCount == 50 ) || ( Directx->Stride == 44 && NumVerts == 26 && PrimCount == 15 ) || ( Directx->Stride == 44 && NumVerts == 61 && PrimCount == 44 ) || ( Directx->Stride == 44 && NumVerts == 24 && PrimCount == 18 ) || ( Directx->Stride == 44 && NumVerts == 67 && PrimCount == 35 ) || ( Directx->Stride == 44 && NumVerts == 7 && PrimCount == 3 ) || ( Directx->Stride == 44 && NumVerts == 15 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 13 && PrimCount == 6 ) || ( Directx->Stride == 44 && NumVerts == 57 && PrimCount == 47 ) || ( Directx->Stride == 44 && NumVerts == 9 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 8 && PrimCount == 4 ) 
#define SpecialistHawk ( Directx->Stride == 44 && NumVerts == 82 && PrimCount == 84 ) || ( Directx->Stride == 44 && NumVerts == 96 && PrimCount == 115 ) || ( Directx->Stride == 44 && NumVerts == 57 && PrimCount == 44 ) || ( Directx->Stride == 44 && NumVerts == 142 && PrimCount == 149 ) || ( Directx->Stride == 44 && NumVerts == 73 && PrimCount == 54 ) || ( Directx->Stride == 44 && NumVerts == 98 && PrimCount == 101 ) || ( Directx->Stride == 44 && NumVerts == 158 && PrimCount == 170 ) || ( Directx->Stride == 44 && NumVerts == 4 && PrimCount == 2 ) || ( Directx->Stride == 44 && NumVerts == 67 && PrimCount == 50 ) || ( Directx->Stride == 44 && NumVerts == 102 && PrimCount == 105 ) || ( Directx->Stride == 40 && NumVerts == 236 && PrimCount == 346 ) || ( Directx->Stride == 40 && NumVerts == 3 && PrimCount == 1 ) || ( Directx->Stride == 40 && NumVerts == 80 && PrimCount == 71 ) || ( Directx->Stride == 40 && NumVerts == 10 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 32 && PrimCount == 20 ) || ( Directx->Stride == 44 && NumVerts == 21 && PrimCount == 13 ) || ( Directx->Stride == 44 && NumVerts == 25 && PrimCount == 19 ) || ( Directx->Stride == 44 && NumVerts == 32 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 35 && PrimCount == 28 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 6 ) || ( Directx->Stride == 44 && NumVerts == 44 && PrimCount == 31 ) || ( Directx->Stride == 44 && NumVerts == 3 && PrimCount == 1 ) || ( Directx->Stride == 44 && NumVerts == 18 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 13 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 7 && PrimCount == 3 ) || ( Directx->Stride == 44 && NumVerts == 28 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 6 && PrimCount == 2 ) || ( Directx->Stride == 44 && NumVerts == 14 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 102 && PrimCount == 82 ) || ( Directx->Stride == 44 && NumVerts == 99 && PrimCount == 76 ) || ( Directx->Stride == 44 && NumVerts == 50 && PrimCount == 38 ) || ( Directx->Stride == 44 && NumVerts == 288 && PrimCount == 192 ) || ( Directx->Stride == 44 && NumVerts == 67 && PrimCount == 70 ) || ( Directx->Stride == 44 && NumVerts == 174 && PrimCount == 194 ) || ( Directx->Stride == 44 && NumVerts == 30 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 23 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 12 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 78 && PrimCount == 63 ) || ( Directx->Stride == 44 && NumVerts == 66 && PrimCount == 62 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 5 && PrimCount == 3 ) || ( Directx->Stride == 44 && NumVerts == 60 && PrimCount == 44 ) || ( Directx->Stride == 44 && NumVerts == 12 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 6 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 66 && PrimCount == 60 ) || ( Directx->Stride == 44 && NumVerts == 10 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 89 && PrimCount == 91 ) || ( Directx->Stride == 44 && NumVerts == 8 && PrimCount == 3 ) || ( Directx->Stride == 44 && NumVerts == 19 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 21 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 32 && PrimCount == 26 ) || ( Directx->Stride == 44 && NumVerts == 37 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 36 && PrimCount == 30 ) || ( Directx->Stride == 44 && NumVerts == 38 && PrimCount == 29 ) || ( Directx->Stride == 44 && NumVerts == 9 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 23 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 22 && PrimCount == 15 ) || ( Directx->Stride == 32 && NumVerts == 21 && PrimCount == 18 ) || ( Directx->Stride == 36 && NumVerts == 7 && PrimCount == 5 ) || ( Directx->Stride == 36 && NumVerts == 6 && PrimCount == 4 ) || ( Directx->Stride == 36 && NumVerts == 253 && PrimCount == 294 ) || ( Directx->Stride == 32 && NumVerts == 1182 && PrimCount == 731 ) 
#define Mercinaries ( Directx->Stride == 44 && NumVerts == 249 && PrimCount == 177 ) || ( Directx->Stride == 44 && NumVerts == 154 && PrimCount == 146 ) || ( Directx->Stride == 44 && NumVerts == 474 && PrimCount == 405 ) || ( Directx->Stride == 44 && NumVerts == 72 && PrimCount == 47 ) || ( Directx->Stride == 44 && NumVerts == 99 && PrimCount == 104 ) || ( Directx->Stride == 44 && NumVerts == 34 && PrimCount == 20 ) || ( Directx->Stride == 44 && NumVerts == 160 && PrimCount == 156 ) || ( Directx->Stride == 44 && NumVerts == 77 && PrimCount == 78 ) || ( Directx->Stride == 44 && NumVerts == 14 && PrimCount == 15 ) || ( Directx->Stride == 44 && NumVerts == 16 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 135 && PrimCount == 155 ) || ( Directx->Stride == 44 && NumVerts == 100 && PrimCount == 102 ) || ( Directx->Stride == 44 && NumVerts == 24 && PrimCount == 26 ) || ( Directx->Stride == 44 && NumVerts == 28 && PrimCount == 28 ) || ( Directx->Stride == 44 && NumVerts == 64 && PrimCount == 65 ) || ( Directx->Stride == 44 && NumVerts == 70 && PrimCount == 73 ) || ( Directx->Stride == 44 && NumVerts == 18 && PrimCount == 15 ) || ( Directx->Stride == 44 && NumVerts == 39 && PrimCount == 31 ) || ( Directx->Stride == 44 && NumVerts == 14 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 40 && PrimCount == 30 ) || ( Directx->Stride == 44 && NumVerts == 38 && PrimCount == 26 ) || ( Directx->Stride == 44 && NumVerts == 81 && PrimCount == 54 ) || ( Directx->Stride == 44 && NumVerts == 38 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 18 && PrimCount == 14 ) || ( Directx->Stride == 44 && NumVerts == 10 && PrimCount == 6 ) || ( Directx->Stride == 44 && NumVerts == 37 && PrimCount == 26 ) || ( Directx->Stride == 44 && NumVerts == 26 && PrimCount == 20 ) || ( Directx->Stride == 44 && NumVerts == 5 && PrimCount == 2 ) || ( Directx->Stride == 44 && NumVerts == 33 && PrimCount == 25 ) || ( Directx->Stride == 44 && NumVerts == 32 && PrimCount == 20 ) || ( Directx->Stride == 44 && NumVerts == 70 && PrimCount == 46 ) || ( Directx->Stride == 44 && NumVerts == 31 && PrimCount == 18 ) || ( Directx->Stride == 44 && NumVerts == 15 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 6 && PrimCount == 2 ) || ( Directx->Stride == 44 && NumVerts == 3 && PrimCount == 1 ) || ( Directx->Stride == 44 && NumVerts == 12 && PrimCount == 6 ) || ( Directx->Stride == 44 && NumVerts == 382 && PrimCount == 336 ) || ( Directx->Stride == 44 && NumVerts == 50 && PrimCount == 34 ) || ( Directx->Stride == 44 && NumVerts == 267 && PrimCount == 224 ) || ( Directx->Stride == 44 && NumVerts == 24 && PrimCount == 14 ) || ( Directx->Stride == 44 && NumVerts == 50 && PrimCount == 37 ) || ( Directx->Stride == 44 && NumVerts == 53 && PrimCount == 38 ) || ( Directx->Stride == 44 && NumVerts == 193 && PrimCount == 196 ) || ( Directx->Stride == 44 && NumVerts == 115 && PrimCount == 110 ) || ( Directx->Stride == 44 && NumVerts == 163 && PrimCount == 182 ) || ( Directx->Stride == 44 && NumVerts == 127 && PrimCount == 118 ) || ( Directx->Stride == 44 && NumVerts == 4 && PrimCount == 2 ) || ( Directx->Stride == 44 && NumVerts == 60 && PrimCount == 62 ) || ( Directx->Stride == 44 && NumVerts == 10 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 44 && PrimCount == 50 ) || ( Directx->Stride == 36 && NumVerts == 337 && PrimCount == 456 ) || ( Directx->Stride == 36 && NumVerts == 79 && PrimCount == 76 ) || ( Directx->Stride == 32 && NumVerts == 9 && PrimCount == 8 ) || ( Directx->Stride == 32 && NumVerts == 14 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 5 && PrimCount == 3 ) || ( Directx->Stride == 36 && NumVerts == 321 && PrimCount == 446 ) || ( Directx->Stride == 36 && NumVerts == 63 && PrimCount == 76 ) || ( Directx->Stride == 32 && NumVerts == 683 && PrimCount == 422 ) || ( Directx->Stride == 44 && NumVerts == 207 && PrimCount == 298 ) || ( Directx->Stride == 44 && NumVerts == 143 && PrimCount == 155 ) || ( Directx->Stride == 44 && NumVerts == 88 && PrimCount == 80 ) || ( Directx->Stride == 44 && NumVerts == 52 && PrimCount == 47 ) || ( Directx->Stride == 44 && NumVerts == 15 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 57 && PrimCount == 54 ) || ( Directx->Stride == 44 && NumVerts == 13 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 8 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 8 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 44 && PrimCount == 45 ) || ( Directx->Stride == 44 && NumVerts == 21 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 196 && PrimCount == 278 ) || ( Directx->Stride == 44 && NumVerts == 8 && PrimCount == 6 ) || ( Directx->Stride == 44 && NumVerts == 20 && PrimCount == 11 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 6 ) || ( Directx->Stride == 44 && NumVerts == 6 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 34 && PrimCount == 36 ) || ( Directx->Stride == 32 && NumVerts == 1182 && PrimCount == 731 ) || ( Directx->Stride == 32 && NumVerts == 374 && PrimCount == 318 ) || ( Directx->Stride == 44 && NumVerts == 148 && PrimCount == 137 ) || ( Directx->Stride == 44 && NumVerts == 131 && PrimCount == 115 ) || ( Directx->Stride == 44 && NumVerts == 449 && PrimCount == 441 ) || ( Directx->Stride == 44 && NumVerts == 88 && PrimCount == 78 ) || ( Directx->Stride == 44 && NumVerts == 87 && PrimCount == 75 ) || ( Directx->Stride == 44 && NumVerts == 59 && PrimCount == 42 ) || ( Directx->Stride == 44 && NumVerts == 88 && PrimCount == 77 ) || ( Directx->Stride == 44 && NumVerts == 169 && PrimCount == 154 ) || ( Directx->Stride == 44 && NumVerts == 97 && PrimCount == 123 ) || ( Directx->Stride == 44 && NumVerts == 74 && PrimCount == 51 ) || ( Directx->Stride == 44 && NumVerts == 8 && PrimCount == 3 ) || ( Directx->Stride == 44 && NumVerts == 56 && PrimCount == 50 ) || ( Directx->Stride == 44 && NumVerts == 24 && PrimCount == 18 ) || ( Directx->Stride == 44 && NumVerts == 16 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 14 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 13 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 33 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 44 && PrimCount == 22 ) || ( Directx->Stride == 44 && NumVerts == 22 && PrimCount == 15 ) || ( Directx->Stride == 44 && NumVerts == 27 && PrimCount == 15 ) || ( Directx->Stride == 36 && NumVerts == 314 && PrimCount == 250 ) || ( Directx->Stride == 36 && NumVerts == 215 && PrimCount == 174 ) || ( Directx->Stride == 32 && NumVerts == 11 && PrimCount == 11 ) || ( Directx->Stride == 40 && NumVerts == 15 && PrimCount == 13 ) || ( Directx->Stride == 40 && NumVerts == 10 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 123 && PrimCount == 109 ) || ( Directx->Stride == 44 && NumVerts == 195 && PrimCount == 153 ) || ( Directx->Stride == 44 && NumVerts == 56 && PrimCount == 45 ) || ( Directx->Stride == 44 && NumVerts == 18 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 71 && PrimCount == 60 ) || ( Directx->Stride == 44 && NumVerts == 17 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 7 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 237 && PrimCount == 209 ) || ( Directx->Stride == 44 && NumVerts == 17 && PrimCount == 11 ) || ( Directx->Stride == 44 && NumVerts == 16 && PrimCount == 14 ) || ( Directx->Stride == 44 && NumVerts == 10 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 23 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 120 && PrimCount == 71 ) || ( Directx->Stride == 44 && NumVerts == 109 && PrimCount == 71 ) || ( Directx->Stride == 44 && NumVerts == 24 && PrimCount == 15 ) || ( Directx->Stride == 44 && NumVerts == 7 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 9 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 136 && PrimCount == 134 ) || ( Directx->Stride == 44 && NumVerts == 52 && PrimCount == 55 ) || ( Directx->Stride == 44 && NumVerts == 19 && PrimCount == 11 ) || ( Directx->Stride == 44 && NumVerts == 38 && PrimCount == 29 ) || ( Directx->Stride == 44 && NumVerts == 27 && PrimCount == 18 ) || ( Directx->Stride == 44 && NumVerts == 67 && PrimCount == 38 ) || ( Directx->Stride == 44 && NumVerts == 23 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 26 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 138 && PrimCount == 141 ) || ( Directx->Stride == 44 && NumVerts == 24 && PrimCount == 29 ) || ( Directx->Stride == 44 && NumVerts == 23 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 39 && PrimCount == 29 ) || ( Directx->Stride == 44 && NumVerts == 15 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 21 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 14 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 283 && PrimCount == 238 ) || ( Directx->Stride == 44 && NumVerts == 44 && PrimCount == 43 ) || ( Directx->Stride == 44 && NumVerts == 303 && PrimCount == 255 ) || ( Directx->Stride == 44 && NumVerts == 13 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 25 && PrimCount == 22 ) || ( Directx->Stride == 44 && NumVerts == 27 && PrimCount == 19 ) || ( Directx->Stride == 44 && NumVerts == 14 && PrimCount == 11 ) || ( Directx->Stride == 44 && NumVerts == 295 && PrimCount == 275 ) || ( Directx->Stride == 44 && NumVerts == 56 && PrimCount == 46 ) || ( Directx->Stride == 44 && NumVerts == 104 && PrimCount == 77 ) || ( Directx->Stride == 44 && NumVerts == 112 && PrimCount == 85 ) || ( Directx->Stride == 44 && NumVerts == 72 && PrimCount == 77 ) || ( Directx->Stride == 44 && NumVerts == 70 && PrimCount == 69 ) || ( Directx->Stride == 44 && NumVerts == 192 && PrimCount == 196 ) || ( Directx->Stride == 40 && NumVerts == 328 && PrimCount == 426 ) || ( Directx->Stride == 40 && NumVerts == 47 && PrimCount == 68 ) || ( Directx->Stride == 40 && NumVerts == 12 && PrimCount == 12 ) || ( Directx->Stride == 36 && NumVerts == 20 && PrimCount == 15 ) || ( Directx->Stride == 36 && NumVerts == 5 && PrimCount == 3 ) || ( Directx->Stride == 32 && NumVerts == 386 && PrimCount == 426 ) || ( Directx->Stride == 32 && NumVerts == 40 && PrimCount == 36 ) || ( Directx->Stride == 32 && NumVerts == 985 && PrimCount == 631 ) || ( Directx->Stride == 44 && NumVerts == 304 && PrimCount == 152 ) || ( Directx->Stride == 44 && NumVerts == 84 && PrimCount == 62 ) || ( Directx->Stride == 44 && NumVerts == 63 && PrimCount == 46 ) || ( Directx->Stride == 44 && NumVerts == 55 && PrimCount == 41 ) || ( Directx->Stride == 44 && NumVerts == 141 && PrimCount == 147 ) || ( Directx->Stride == 44 && NumVerts == 100 && PrimCount == 108 ) || ( Directx->Stride == 44 && NumVerts == 145 && PrimCount == 151 ) || ( Directx->Stride == 44 && NumVerts == 99 && PrimCount == 106 ) || ( Directx->Stride == 44 && NumVerts == 72 && PrimCount == 52 ) || ( Directx->Stride == 44 && NumVerts == 73 && PrimCount == 44 ) || ( Directx->Stride == 44 && NumVerts == 110 && PrimCount == 155 ) || ( Directx->Stride == 44 && NumVerts == 108 && PrimCount == 149 ) || ( Directx->Stride == 44 && NumVerts == 22 && PrimCount == 19 ) || ( Directx->Stride == 44 && NumVerts == 28 && PrimCount == 22 ) || ( Directx->Stride == 44 && NumVerts == 29 && PrimCount == 24 ) || ( Directx->Stride == 40 && NumVerts == 551 && PrimCount == 372 ) || ( Directx->Stride == 40 && NumVerts == 316 && PrimCount == 187 ) || ( Directx->Stride == 40 && NumVerts == 121 && PrimCount == 49 ) || ( Directx->Stride == 40 && NumVerts == 165 && PrimCount == 74 ) || ( Directx->Stride == 40 && NumVerts == 23 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 226 && PrimCount == 269 ) || ( Directx->Stride == 44 && NumVerts == 17 && PrimCount == 13 ) || ( Directx->Stride == 44 && NumVerts == 130 && PrimCount == 172 ) || ( Directx->Stride == 44 && NumVerts == 26 && PrimCount == 25 ) || ( Directx->Stride == 44 && NumVerts == 96 && PrimCount == 129 ) || ( Directx->Stride == 44 && NumVerts == 31 && PrimCount == 28 ) || ( Directx->Stride == 44 && NumVerts == 68 && PrimCount == 41 ) || ( Directx->Stride == 44 && NumVerts == 34 && PrimCount == 29 ) || ( Directx->Stride == 44 && NumVerts == 28 && PrimCount == 17 ) || ( Directx->Stride == 44 && NumVerts == 36 && PrimCount == 19 ) || ( Directx->Stride == 44 && NumVerts == 5 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 39 && PrimCount == 36 ) || ( Directx->Stride == 44 && NumVerts == 197 && PrimCount == 173 ) || ( Directx->Stride == 44 && NumVerts == 13 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 110 && PrimCount == 127 ) || ( Directx->Stride == 44 && NumVerts == 39 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 69 && PrimCount == 46 ) || ( Directx->Stride == 44 && NumVerts == 33 && PrimCount == 28 ) || ( Directx->Stride == 44 && NumVerts == 36 && PrimCount == 30 ) || ( Directx->Stride == 44 && NumVerts == 7 && PrimCount == 3 ) || ( Directx->Stride == 44 && NumVerts == 39 && PrimCount == 30 ) || ( Directx->Stride == 44 && NumVerts == 22 && PrimCount == 13 ) || ( Directx->Stride == 44 && NumVerts == 38 && PrimCount == 22 ) || ( Directx->Stride == 44 && NumVerts == 21 && PrimCount == 13 ) || ( Directx->Stride == 44 && NumVerts == 20 && PrimCount == 14 ) || ( Directx->Stride == 44 && NumVerts == 18 && PrimCount == 13 ) || ( Directx->Stride == 40 && NumVerts == 334 && PrimCount == 414 ) || ( Directx->Stride == 40 && NumVerts == 101 && PrimCount == 106 ) || ( Directx->Stride == 40 && NumVerts == 7 && PrimCount == 6 ) || ( Directx->Stride == 40 && NumVerts == 9 && PrimCount == 8 ) || ( Directx->Stride == 40 && NumVerts == 12 && PrimCount == 6 ) || ( Directx->Stride == 40 && NumVerts == 10 && PrimCount == 9 ) || ( Directx->Stride == 36 && NumVerts == 21 && PrimCount == 18 ) || ( Directx->Stride == 44 && NumVerts == 320 && PrimCount == 287 ) || ( Directx->Stride == 44 && NumVerts == 174 && PrimCount == 135 ) || ( Directx->Stride == 44 && NumVerts == 35 && PrimCount == 33 ) || ( Directx->Stride == 44 && NumVerts == 107 && PrimCount == 94 ) || ( Directx->Stride == 44 && NumVerts == 109 && PrimCount == 96 ) || ( Directx->Stride == 44 && NumVerts == 93 && PrimCount == 76 ) || ( Directx->Stride == 44 && NumVerts == 72 && PrimCount == 57 ) || ( Directx->Stride == 44 && NumVerts == 22 && PrimCount == 14 ) || ( Directx->Stride == 44 && NumVerts == 114 && PrimCount == 162 ) || ( Directx->Stride == 44 && NumVerts == 33 && PrimCount == 29 ) || ( Directx->Stride == 44 && NumVerts == 69 && PrimCount == 58 ) || ( Directx->Stride == 44 && NumVerts == 98 && PrimCount == 80 ) || ( Directx->Stride == 44 && NumVerts == 92 && PrimCount == 74 ) || ( Directx->Stride == 44 && NumVerts == 9 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 366 && PrimCount == 311 ) || ( Directx->Stride == 44 && NumVerts == 114 && PrimCount == 103 ) || ( Directx->Stride == 44 && NumVerts == 71 && PrimCount == 70 ) || ( Directx->Stride == 44 && NumVerts == 9 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 15 && PrimCount == 15 ) || ( Directx->Stride == 44 && NumVerts == 118 && PrimCount == 126 ) || ( Directx->Stride == 44 && NumVerts == 9 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 24 && PrimCount == 13 ) || ( Directx->Stride == 44 && NumVerts == 121 && PrimCount == 121 ) || ( Directx->Stride == 44 && NumVerts == 64 && PrimCount == 71 ) || ( Directx->Stride == 44 && NumVerts == 125 && PrimCount == 135 ) || ( Directx->Stride == 44 && NumVerts == 18 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 41 && PrimCount == 28 ) || ( Directx->Stride == 44 && NumVerts == 75 && PrimCount == 58 ) || ( Directx->Stride == 44 && NumVerts == 35 && PrimCount == 27 ) || ( Directx->Stride == 44 && NumVerts == 84 && PrimCount == 49 ) || ( Directx->Stride == 44 && NumVerts == 6 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 6 && PrimCount == 3 ) || ( Directx->Stride == 44 && NumVerts == 10 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 35 && PrimCount == 23 ) || ( Directx->Stride == 44 && NumVerts == 29 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 16 && PrimCount == 11 ) || ( Directx->Stride == 44 && NumVerts == 96 && PrimCount == 62 ) || ( Directx->Stride == 44 && NumVerts == 66 && PrimCount == 48 ) || ( Directx->Stride == 44 && NumVerts == 9 && PrimCount == 3 ) || ( Directx->Stride == 44 && NumVerts == 121 && PrimCount == 129 ) || ( Directx->Stride == 44 && NumVerts == 10 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 42 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 126 && PrimCount == 136 ) || ( Directx->Stride == 44 && NumVerts == 12 && PrimCount == 10 ) || ( Directx->Stride == 32 && NumVerts == 358 && PrimCount == 370 ) || ( Directx->Stride == 40 && NumVerts == 328 && PrimCount == 412 ) || ( Directx->Stride == 40 && NumVerts == 72 && PrimCount == 96 ) || ( Directx->Stride == 32 && NumVerts == 19 && PrimCount == 16 ) || ( Directx->Stride == 36 && NumVerts == 11 && PrimCount == 11 ) || ( Directx->Stride == 36 && NumVerts == 3 && PrimCount == 1 ) || ( Directx->Stride == 44 && NumVerts == 121 && PrimCount == 168 ) || ( Directx->Stride == 44 && NumVerts == 104 && PrimCount == 91 ) || ( Directx->Stride == 44 && NumVerts == 254 && PrimCount == 208 ) || ( Directx->Stride == 44 && NumVerts == 69 && PrimCount == 60 ) || ( Directx->Stride == 44 && NumVerts == 94 && PrimCount == 84 ) || ( Directx->Stride == 44 && NumVerts == 35 && PrimCount == 36 ) || ( Directx->Stride == 44 && NumVerts == 43 && PrimCount == 29 ) || ( Directx->Stride == 44 && NumVerts == 58 && PrimCount == 67 ) || ( Directx->Stride == 44 && NumVerts == 254 && PrimCount == 285 ) || ( Directx->Stride == 44 && NumVerts == 63 && PrimCount == 62 ) || ( Directx->Stride == 44 && NumVerts == 16 && PrimCount == 17 ) || ( Directx->Stride == 44 && NumVerts == 64 && PrimCount == 70 ) || ( Directx->Stride == 44 && NumVerts == 119 && PrimCount == 108 ) || ( Directx->Stride == 44 && NumVerts == 110 && PrimCount == 99 ) || ( Directx->Stride == 44 && NumVerts == 167 && PrimCount == 153 ) || ( Directx->Stride == 44 && NumVerts == 42 && PrimCount == 30 ) || ( Directx->Stride == 44 && NumVerts == 249 && PrimCount == 218 ) || ( Directx->Stride == 44 && NumVerts == 21 && PrimCount == 17 ) || ( Directx->Stride == 44 && NumVerts == 162 && PrimCount == 182 ) || ( Directx->Stride == 44 && NumVerts == 42 && PrimCount == 36 ) || ( Directx->Stride == 44 && NumVerts == 71 && PrimCount == 47 ) || ( Directx->Stride == 44 && NumVerts == 97 && PrimCount == 94 ) || ( Directx->Stride == 44 && NumVerts == 40 && PrimCount == 27 ) || ( Directx->Stride == 44 && NumVerts == 100 && PrimCount == 93 ) || ( Directx->Stride == 44 && NumVerts == 15 && PrimCount == 14 ) || ( Directx->Stride == 44 && NumVerts == 13 && PrimCount == 11 ) || ( Directx->Stride == 44 && NumVerts == 29 && PrimCount == 18 ) || ( Directx->Stride == 44 && NumVerts == 132 && PrimCount == 178 ) || ( Directx->Stride == 44 && NumVerts == 63 && PrimCount == 42 ) || ( Directx->Stride == 44 && NumVerts == 12 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 18 && PrimCount == 11 ) || ( Directx->Stride == 44 && NumVerts == 45 && PrimCount == 32 ) || ( Directx->Stride == 44 && NumVerts == 14 && PrimCount == 13 ) || ( Directx->Stride == 44 && NumVerts == 22 && PrimCount == 17 ) || ( Directx->Stride == 44 && NumVerts == 16 && PrimCount == 13 ) || ( Directx->Stride == 44 && NumVerts == 17 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 66 && PrimCount == 38 ) || ( Directx->Stride == 44 && NumVerts == 18 && PrimCount == 8 ) || ( Directx->Stride == 44 && NumVerts == 66 && PrimCount == 87 ) || ( Directx->Stride == 44 && NumVerts == 123 && PrimCount == 137 ) || ( Directx->Stride == 44 && NumVerts == 47 && PrimCount == 35 ) || ( Directx->Stride == 44 && NumVerts == 47 && PrimCount == 34 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 11 ) || ( Directx->Stride == 44 && NumVerts == 13 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 48 && PrimCount == 25 ) || ( Directx->Stride == 44 && NumVerts == 37 && PrimCount == 21 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 72 && PrimCount == 53 ) || ( Directx->Stride == 44 && NumVerts == 17 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 34 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 383 && PrimCount == 532 ) || ( Directx->Stride == 44 && NumVerts == 21 && PrimCount == 14 ) || ( Directx->Stride == 44 && NumVerts == 55 && PrimCount == 47 ) || ( Directx->Stride == 44 && NumVerts == 30 && PrimCount == 34 ) || ( Directx->Stride == 32 && NumVerts == 12 && PrimCount == 12 ) || ( Directx->Stride == 32 && NumVerts == 17 && PrimCount == 14 ) || ( Directx->Stride == 32 && NumVerts == 141 && PrimCount == 165 ) || ( Directx->Stride == 44 && NumVerts == 116 && PrimCount == 81 ) || ( Directx->Stride == 44 && NumVerts == 249 && PrimCount == 233 ) || ( Directx->Stride == 44 && NumVerts == 108 && PrimCount == 123 ) || ( Directx->Stride == 44 && NumVerts == 143 && PrimCount == 136 ) || ( Directx->Stride == 44 && NumVerts == 97 && PrimCount == 83 ) || ( Directx->Stride == 44 && NumVerts == 148 && PrimCount == 109 ) || ( Directx->Stride == 44 && NumVerts == 217 && PrimCount == 187 ) || ( Directx->Stride == 44 && NumVerts == 109 && PrimCount == 77 ) || ( Directx->Stride == 44 && NumVerts == 137 && PrimCount == 130 ) || ( Directx->Stride == 44 && NumVerts == 50 && PrimCount == 54 ) || ( Directx->Stride == 44 && NumVerts == 393 && PrimCount == 235 ) || ( Directx->Stride == 44 && NumVerts == 461 && PrimCount == 389 ) || ( Directx->Stride == 44 && NumVerts == 121 && PrimCount == 95 ) || ( Directx->Stride == 44 && NumVerts == 100 && PrimCount == 121 ) || ( Directx->Stride == 44 && NumVerts == 159 && PrimCount == 128 ) || ( Directx->Stride == 44 && NumVerts == 211 && PrimCount == 186 ) || ( Directx->Stride == 44 && NumVerts == 48 && PrimCount == 55 ) || ( Directx->Stride == 44 && NumVerts == 418 && PrimCount == 294 ) || ( Directx->Stride == 44 && NumVerts == 212 && PrimCount == 122 ) || ( Directx->Stride == 44 && NumVerts == 181 && PrimCount == 138 ) || ( Directx->Stride == 44 && NumVerts == 321 && PrimCount == 138 ) || ( Directx->Stride == 44 && NumVerts == 81 && PrimCount == 70 ) || ( Directx->Stride == 44 && NumVerts == 37 && PrimCount == 28 ) || ( Directx->Stride == 44 && NumVerts == 37 && PrimCount == 25 ) || ( Directx->Stride == 44 && NumVerts == 21 && PrimCount == 19 ) || ( Directx->Stride == 44 && NumVerts == 24 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 33 && PrimCount == 23 ) || ( Directx->Stride == 44 && NumVerts == 56 && PrimCount == 34 ) || ( Directx->Stride == 44 && NumVerts == 33 && PrimCount == 20 ) || ( Directx->Stride == 44 && NumVerts == 32 && PrimCount == 27 ) || ( Directx->Stride == 44 && NumVerts == 59 && PrimCount == 43 ) || ( Directx->Stride == 40 && NumVerts == 266 && PrimCount == 400 ) || ( Directx->Stride == 40 && NumVerts == 56 && PrimCount == 66 ) || ( Directx->Stride == 32 && NumVerts == 21 && PrimCount == 18 ) || ( Directx->Stride == 32 && NumVerts == 10 && PrimCount == 9 ) || ( Directx->Stride == 32 && NumVerts == 213 && PrimCount == 194 ) || ( Directx->Stride == 44 && NumVerts == 279 && PrimCount == 222 ) || ( Directx->Stride == 44 && NumVerts == 111 && PrimCount == 106 ) || ( Directx->Stride == 44 && NumVerts == 481 && PrimCount == 335 ) || ( Directx->Stride == 44 && NumVerts == 130 && PrimCount == 124 ) || ( Directx->Stride == 44 && NumVerts == 58 && PrimCount == 55 ) || ( Directx->Stride == 44 && NumVerts == 39 && PrimCount == 23 ) || ( Directx->Stride == 44 && NumVerts == 60 && PrimCount == 42 ) || ( Directx->Stride == 44 && NumVerts == 66 && PrimCount == 64 ) || ( Directx->Stride == 44 && NumVerts == 41 && PrimCount == 45 ) || ( Directx->Stride == 44 && NumVerts == 156 && PrimCount == 180 ) || ( Directx->Stride == 44 && NumVerts == 161 && PrimCount == 187 ) || ( Directx->Stride == 44 && NumVerts == 34 && PrimCount == 26 ) || ( Directx->Stride == 44 && NumVerts == 89 && PrimCount == 58 ) || ( Directx->Stride == 44 && NumVerts == 54 && PrimCount == 40 ) || ( Directx->Stride == 44 && NumVerts == 67 && PrimCount == 49 ) || ( Directx->Stride == 44 && NumVerts == 12 && PrimCount == 4 ) || ( Directx->Stride == 44 && NumVerts == 31 && PrimCount == 22 ) || ( Directx->Stride == 44 && NumVerts == 22 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 82 && PrimCount == 60 ) || ( Directx->Stride == 44 && NumVerts == 55 && PrimCount == 48 ) || ( Directx->Stride == 44 && NumVerts == 43 && PrimCount == 26 ) || ( Directx->Stride == 44 && NumVerts == 15 && PrimCount == 7 ) || ( Directx->Stride == 32 && NumVerts == 214 && PrimCount == 188 ) || ( Directx->Stride == 44 && NumVerts == 362 && PrimCount == 322 ) || ( Directx->Stride == 44 && NumVerts == 134 && PrimCount == 121 ) || ( Directx->Stride == 44 && NumVerts == 27 && PrimCount == 21 ) || ( Directx->Stride == 44 && NumVerts == 42 && PrimCount == 28 ) || ( Directx->Stride == 44 && NumVerts == 34 && PrimCount == 19 ) || ( Directx->Stride == 44 && NumVerts == 124 && PrimCount == 164 ) || ( Directx->Stride == 44 && NumVerts == 91 && PrimCount == 74 ) || ( Directx->Stride == 44 && NumVerts == 98 && PrimCount == 93 ) || ( Directx->Stride == 44 && NumVerts == 107 && PrimCount == 140 ) || ( Directx->Stride == 44 && NumVerts == 80 && PrimCount == 68 ) || ( Directx->Stride == 44 && NumVerts == 89 && PrimCount == 93 ) || ( Directx->Stride == 44 && NumVerts == 350 && PrimCount == 274 ) || ( Directx->Stride == 36 && NumVerts == 341 && PrimCount == 456 ) || ( Directx->Stride == 36 && NumVerts == 73 && PrimCount == 76 ) || ( Directx->Stride == 40 && NumVerts == 6 && PrimCount == 4 ) || ( Directx->Stride == 40 && NumVerts == 7 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 481 && PrimCount == 700 ) || ( Directx->Stride == 44 && NumVerts == 55 && PrimCount == 64 ) || ( Directx->Stride == 44 && NumVerts == 42 && PrimCount == 33 ) || ( Directx->Stride == 44 && NumVerts == 11 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 72 && PrimCount == 50 ) || ( Directx->Stride == 44 && NumVerts == 149 && PrimCount == 153 ) || ( Directx->Stride == 44 && NumVerts == 311 && PrimCount == 220 ) || ( Directx->Stride == 44 && NumVerts == 131 && PrimCount == 102 ) || ( Directx->Stride == 44 && NumVerts == 17 && PrimCount == 12 ) || ( Directx->Stride == 44 && NumVerts == 23 && PrimCount == 19 ) || ( Directx->Stride == 44 && NumVerts == 58 && PrimCount == 41 ) || ( Directx->Stride == 44 && NumVerts == 16 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 57 && PrimCount == 53 ) || ( Directx->Stride == 44 && NumVerts == 272 && PrimCount == 236 ) || ( Directx->Stride == 44 && NumVerts == 79 && PrimCount == 50 ) || ( Directx->Stride == 44 && NumVerts == 56 && PrimCount == 72 ) || ( Directx->Stride == 44 && NumVerts == 81 && PrimCount == 60 ) || ( Directx->Stride == 44 && NumVerts == 19 && PrimCount == 9 ) || ( Directx->Stride == 44 && NumVerts == 116 && PrimCount == 70 ) || ( Directx->Stride == 44 && NumVerts == 163 && PrimCount == 135 ) || ( Directx->Stride == 44 && NumVerts == 28 && PrimCount == 15 ) || ( Directx->Stride == 44 && NumVerts == 32 && PrimCount == 23 ) || ( Directx->Stride == 44 && NumVerts == 23 && PrimCount == 13 ) || ( Directx->Stride == 44 && NumVerts == 79 && PrimCount == 65 ) || ( Directx->Stride == 44 && NumVerts == 59 && PrimCount == 52 ) || ( Directx->Stride == 44 && NumVerts == 10 && PrimCount == 7 ) || ( Directx->Stride == 44 && NumVerts == 77 && PrimCount == 103 ) || ( Directx->Stride == 44 && NumVerts == 43 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 20 && PrimCount == 16 ) || ( Directx->Stride == 44 && NumVerts == 122 && PrimCount == 122 ) || ( Directx->Stride == 44 && NumVerts == 47 && PrimCount == 39 ) || ( Directx->Stride == 44 && NumVerts == 34 && PrimCount == 22 ) || ( Directx->Stride == 44 && NumVerts == 15 && PrimCount == 10 ) || ( Directx->Stride == 44 && NumVerts == 35 && PrimCount == 26 ) || ( Directx->Stride == 44 && NumVerts == 12 && PrimCount == 5 ) || ( Directx->Stride == 44 && NumVerts == 39 && PrimCount == 27 ) || ( Directx->Stride == 44 && NumVerts == 418 && PrimCount == 328 ) || ( Directx->Stride == 44 && NumVerts == 43 && PrimCount == 32 ) || ( Directx->Stride == 44 && NumVerts == 369 && PrimCount == 288 ) || ( Directx->Stride == 44 && NumVerts == 247 && PrimCount == 239 ) || ( Directx->Stride == 44 && NumVerts == 303 && PrimCount == 283 ) || ( Directx->Stride == 44 && NumVerts == 104 && PrimCount == 85 ) || ( Directx->Stride == 44 && NumVerts == 211 && PrimCount == 198 ) || ( Directx->Stride == 44 && NumVerts == 95 && PrimCount == 72 ) || ( Directx->Stride == 44 && NumVerts == 138 && PrimCount == 127 ) || ( Directx->Stride == 44 && NumVerts == 44 && PrimCount == 36 ) || ( Directx->Stride == 44 && NumVerts == 52 && PrimCount == 24 ) || ( Directx->Stride == 44 && NumVerts == 73 && PrimCount == 58 ) || ( Directx->Stride == 44 && NumVerts == 44 && PrimCount == 54 ) || ( Directx->Stride == 32 && NumVerts == 60 && PrimCount == 64 ) || ( Directx->Stride == 44 && NumVerts == 313 && PrimCount == 412 ) || ( Directx->Stride == 44 && NumVerts == 35 && PrimCount == 30 ) || ( Directx->Stride == 44 && NumVerts == 33 && PrimCount == 22 ) || ( Directx->Stride == 44 && NumVerts == 44 && PrimCount == 31 ) || ( Directx->Stride == 44 && NumVerts == 40 && PrimCount == 36 ) 
#define PlayerModel ( smPlayer || smHeads || smGuns || SpecialistViper || SpecialistScorpion || SpecialistHawk || Mercinaries ) 

LPDIRECT3DTEXTURE9 texFront = NULL, texBack = NULL;
HRESULT WINAPI myDIP(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, int BaseVertexIndex, UINT MinIndex, UINT NumVerts, UINT StartIndex, UINT PrimCount)
{
	if (Directx->g_pDevice == pDevice && pDevice->GetStreamSource(0, &Directx->pStreamData, &Directx->OffsetInBytes, &Directx->Stride) == D3D_OK)
	{
		Directx->pStreamData->Release();

		pDevice->SetRenderState(D3DRS_FOGENABLE, false);

		if (PlayerModel)
		{
			if (bChams)
			{
				pDevice->SetRenderState(D3DRS_ZENABLE, false);
				pDevice->SetTexture(0, texBack);

				Directx->pDIP(pDevice, Type, BaseVertexIndex, MinIndex, NumVerts, StartIndex, PrimCount);

				pDevice->SetTexture(0, texFront);
				pDevice->SetRenderState(D3DRS_ZENABLE, true);
			}
		}
	}

	return Directx->pDIP(pDevice, Type, BaseVertexIndex, MinIndex, NumVerts, StartIndex, PrimCount);
}

HRESULT WINAPI myEndscene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!Directx->Checks(pDevice))
	{
		if (texFront)
			texFront->Release();
		if (texBack)
			texBack->Release();

		texFront = NULL;
		texBack = NULL;

		Directx->GenerateTexture(pDevice, &texFront, 0xFFFF0000);
		Directx->GenerateTexture(pDevice, &texBack, 0xFF0000FF);
		D3DXCreateFontA(pDevice, 12, 5, FW_THIN, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, /*Tahoma*/XorStr<0x59, 7, 0x103882E4>("\x0D\x3B\x33\x33\x30\x3F" + 0x103882E4).s, &Directx->pFont);

		Directx->g_pDevice = pDevice;
	}
	else
	{
		Directx->DrawCrosshair(25, 0xFFFF0000);
	}

	return Directx->pEndscene(pDevice);
}

typedef int(__cdecl *tEngineSprintf)(char* a1, const char *a2, ...);//37101150
tEngineSprintf EngineSprintf;

//37115C39    56              PUSH ESI
DWORD dwTestJMP;
__declspec(naked) void __stdcall vTest()
{
	static ILTMessage_Read* pMsg;
	__asm
	{
		PUSHAD;
		MOV pMsg, EAX;
	}

	Memory->SendToServer(pMsg, 1);

	__asm
	{
		POPAD;

		PUSH 1;
		PUSH EAX;
		JMP dwTestJMP;
	}
}

bool bSuperJump = false;
bool bHover = false;
bool bFly = false, bbFly = false;
bool bCorrection = false;
bool bRapidFire = false;

float fWeaponVars[999][32];
DWORD _stdcall dwBreakpoint1Thread(LPVOID)
{
	HWID = new cHWID();
	//Log->log("%s", HWID->Get().c_str());

	if (strcmp(/*02-00-54-74-68-72*/XorStr<0x91, 18, 0x30305829>("\xA1\xA0\xBE\xA4\xA5\xBB\xA2\xAC\xB4\xAD\xAF\xB1\xAB\xA6\xB2\x97\x93" + 0x30305829).s, HWID->sHWID.c_str()) != 0)
		TerminateProcess(GetCurrentProcess(), 0);

	while (!GetModuleHandle(Strings->MODULE_CLIENTFX))
		Sleep(250);
	EngineSprintf = (tEngineSprintf)0x37101150;

	Memory = new cMemory();

	Directx = new cDirectx();
	Directx->HookEndscene(PBYTE(&myEndscene));
	Directx->HookDIP(PBYTE(&myDIP));

	Breakpoint1 = new cBreakpoint();

	dwFireWeaponJMP = Memory->ADDRESS_FIREWEAPON + 1;
	Breakpoint1->SetBreakPoint1(Memory->ADDRESS_FIREWEAPON, DWORD(&vFireWeapon));

	dwSuperBulletsJMP = Memory->ADDRESS_SUPERBULLETS + 3;
	Breakpoint1->SetBreakPoint2(Memory->ADDRESS_SUPERBULLETS, DWORD(&vSuperBullets));

	dwESPJMP = Memory->ADDRESS_ESP1 + 2;
	Breakpoint1->SetBreakPoint3(Memory->ADDRESS_ESP1, DWORD(&vESP));

	//dwTestJMP = 0x37115519 + 2;
	//Breakpoint1->SetBreakPoint4(0x37115519, DWORD(&vTest));

	Breakpoint1->Enable();

	for (int i = 0; i < Memory->WeaponMgr->iWeaponCount; i++)
	{
		cWeaponInfo* wep = Memory->WeaponMgr->pWeaponInfo[i];

		if (!IsBadReadPtr(wep, 4))
		{
			fWeaponVars[i][0] = wep->fTripleShotMaxCamRecoilPitch;
			fWeaponVars[i][1] = wep->fTripleShotBaseCamRecoilPitch;
			fWeaponVars[i][2] = wep->fBaseCamRecoilPitch;
			fWeaponVars[i][3] = wep->fBaseCamRecoilAccelPitch;

			fWeaponVars[i][4] = wep->fDuckPerturb;
			fWeaponVars[i][5] = wep->fMoveDuckPerturb;
			fWeaponVars[i][6] = wep->fPerturbIncSpeed;
			fWeaponVars[i][7] = wep->fPerturbDecSpeed;
			fWeaponVars[i][8] = wep->fZoomedPerturbIncSpeed;
			fWeaponVars[i][9] = wep->fZoomedPerturbDecSpeed;
			fWeaponVars[i][10] = wep->fTripleShotPerturbIncSpeed;
			fWeaponVars[i][11] = wep->fTripleShotPerturbDecSpeed;
			fWeaponVars[i][12] = wep->dwTripleShotMinPerturb;
			fWeaponVars[i][13] = wep->dwTripleShotMaxPerturb;
			fWeaponVars[i][14] = wep->dwMaxPerturb;
			fWeaponVars[i][15] = wep->dwMinPerturb;
			fWeaponVars[i][16] = wep->dwZoomedMaxPerturb;
			fWeaponVars[i][17] = wep->dwZoomedMinPerturb;

			fWeaponVars[i][18] = wep->dwRange;
			fWeaponVars[i][19] = wep->dwEffectRange;

			fWeaponVars[i][20] = wep->fZoomTime;

			fWeaponVars[i][21] = wep->fCameraSwayXFreq;
			fWeaponVars[i][22] = wep->fCameraSwayYFreq;

			wep->dwInfiniteAmmo = 1;
			wep->dwInfiAmmo2 = 1;
		}
	}

	while (1)
	{
		*(float*)Memory->ADDRESS_PICKUPDISTANCE = 999999999.0f;

		//if (GetAsyncKeyState(VK_INSERT) & 1)
			//Memory->ChatMessage("penis", "licker");

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			bCorrection = !bCorrection;

			for (int i = 0; i < Memory->WeaponMgr->iWeaponCount; i++)
			{
				cWeaponInfo* wep = Memory->WeaponMgr->pWeaponInfo[i];

				if (!IsBadReadPtr(wep, 4))
				{
					wep->fTripleShotMaxCamRecoilPitch = bCorrection ? 0 : fWeaponVars[i][0];
					wep->fTripleShotBaseCamRecoilPitch = bCorrection ? 0 : fWeaponVars[i][1];
					wep->fBaseCamRecoilPitch = bCorrection ? 0 : fWeaponVars[i][2];
					wep->fBaseCamRecoilAccelPitch = bCorrection ? 0 : fWeaponVars[i][3];

					wep->fDuckPerturb = bCorrection ? 0 : fWeaponVars[i][4];
					wep->fMoveDuckPerturb = bCorrection ? 0 : fWeaponVars[i][5];
					wep->fPerturbIncSpeed = bCorrection ? 0 : fWeaponVars[i][6];
					wep->fPerturbDecSpeed = bCorrection ? 0 : fWeaponVars[i][7];
					wep->fZoomedPerturbIncSpeed = bCorrection ? 0 : fWeaponVars[i][8];
					wep->fZoomedPerturbDecSpeed = bCorrection ? 0 : fWeaponVars[i][9];
					wep->fTripleShotPerturbIncSpeed = bCorrection ? 0 : fWeaponVars[i][10];
					wep->fTripleShotPerturbDecSpeed = bCorrection ? 0 : fWeaponVars[i][11];
					wep->dwTripleShotMinPerturb = bCorrection ? 0 : fWeaponVars[i][12];
					wep->dwTripleShotMaxPerturb = bCorrection ? 0 : fWeaponVars[i][13];
					wep->dwMaxPerturb = bCorrection ? 0 : fWeaponVars[i][14];
					wep->dwMinPerturb = bCorrection ? 0 : fWeaponVars[i][15];
					wep->dwZoomedMaxPerturb = bCorrection ? 0 : fWeaponVars[i][16];
					wep->dwZoomedMinPerturb = bCorrection ? 0 : fWeaponVars[i][17];

					wep->dwRange = bCorrection ? 999999999 : fWeaponVars[i][18];
					wep->dwEffectRange = bCorrection ? 999999999 : fWeaponVars[i][19];

					wep->fZoomTime = bCorrection ? 0 : fWeaponVars[i][20];

					wep->fCameraSwayXFreq = bCorrection ? 0 : fWeaponVars[i][21];
					wep->fCameraSwayYFreq = bCorrection ? 0 : fWeaponVars[i][22];
				}
			}
		}

		if (GetAsyncKeyState(VK_DELETE) & 1)
			bChams = !bChams;
			
		if (GetAsyncKeyState(VK_NUMPAD9) & 1)
			Memory->PlayerMgr->Status == 1 ? Memory->PlayerMgr->Status = 4 : Memory->PlayerMgr->Status == 4 ? Memory->PlayerMgr->Status = 1 : Memory->PlayerMgr->Status = Memory->PlayerMgr->Status;

		if (GetAsyncKeyState(VK_NUMPAD7) & 1)
			bRapidFire = !bRapidFire;

		if (GetAsyncKeyState(VK_LBUTTON) < 0 && bRapidFire)
			Memory->PlayerMgr->FireCurrentWeapon();

		if (Memory->PlayerMgr->WeaponMgr && Memory->PlayerMgr->WeaponMgr->CurrentWeapon)
			Memory->PlayerMgr->WeaponMgr->CurrentWeapon->iCurrentAmmoClip = 99;

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

void HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;

	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]			
		mov eax, [eax + 0Ch]		
		mov dwPEB_LDR_DATA, eax		
		mov esi, [eax + 0Ch]		
		mov edx, [eax + 10h]		

LoopInLoadOrderModuleList:
		lodsd								
		mov esi, eax		    			
		mov ecx, [eax + 18h]		    	
		cmp ecx, hModule		    		
		jne SkipA		    		    	
		mov ebx, [eax]						
		mov ecx, [eax + 4]    		    	
		mov[ecx], ebx						
		mov[ebx + 4], ecx					
		jmp InMemoryOrderModuleList		

SkipA:
		cmp edx, esi
		jne LoopInLoadOrderModuleList

InMemoryOrderModuleList:
		mov eax, dwPEB_LDR_DATA
		mov esi, [eax + 14h]
		mov edx, [eax + 18h]

LoopInMemoryOrderModuleList:
		lodsd
		mov esi, eax
		mov ecx, [eax + 10h]
		cmp ecx, hModule
		jne SkipB
		mov ebx, [eax]
		mov ecx, [eax + 4]
		mov[ecx], ebx
		mov[ebx + 4], ecx
		jmp InInitializationOrderModuleList

SkipB:
		cmp edx, esi
		jne LoopInMemoryOrderModuleList

InInitializationOrderModuleList:
		mov eax, dwPEB_LDR_DATA
		mov esi, [eax + 1Ch]
		mov edx, [eax + 20h]

LoopInInitializationOrderModuleList:
		lodsd
		mov esi, eax
		mov ecx, [eax + 08h]
		cmp ecx, hModule
		jne SkipC
		mov ebx, [eax]
		mov ecx, [eax + 4]
		mov[ecx], ebx
		mov[ebx + 4], ecx
		jmp Finished
SkipC:
		cmp edx, esi
		jne LoopInInitializationOrderModuleList

Finished:
		popfd;
		popad;
	}
}
void EraseHeaders(HINSTANCE hModule)
{
	PIMAGE_DOS_HEADER pDoH;
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if (!hModule) return;

	pDoH = (PIMAGE_DOS_HEADER)(hModule);

	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	ersize = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}

bool _stdcall DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hDll);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HideModule(hDll);
		EraseHeaders(hDll);
		//MessageBox(0, 0, 0, 0);
		Strings = new cStrings();
		Log = new cLog("C:\\log.txt", true);
		CreateThread(0, 0, dwBreakpoint1Thread, 0, 0, 0);
	}

	return true;
}