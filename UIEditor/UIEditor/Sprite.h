#pragma once

#include "Header.h"

#include<string>

using namespace std;

class Sprite
{
public:
	Sprite(LPDIRECT3DDEVICE9 pD3DDevice);
	~Sprite(void);

public:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	LPD3DXSPRITE spriteobj;

	LPDIRECT3DTEXTURE9 m_texture;
	LPD3DXFONT m_font;

	//¾«Áé
	LPDIRECT3DTEXTURE9 LoadTexture(string filename, D3DCOLOR transcolor);
	void Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, int x, int y, int width, int height, 
		int frame, int columns, float rotation, float scaleW, float scaleH, D3DCOLOR color);

	//ÎÄ×Ö 
	LPD3DXFONT MakeFont(string name, int size);
	void FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color = D3DCOLOR_XRGB(0,255,0));
};

