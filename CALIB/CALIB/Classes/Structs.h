#ifndef _STRUCTS_
#define _STRUCTS_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

struct Transform
{
	D3DXVECTOR3 Pos;
	unsigned char Space[0x100];
};

#endif