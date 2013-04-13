#pragma once

#include "Header.h"

#include<string>

using namespace std;

class Sprite
{
public:
	Sprite(LPDIRECT3DDEVICE9 pD3DDevice);
	Sprite(LPDIRECT3DDEVICE9 pD3DDevice,string filename, D3DCOLOR transcolor);
	~Sprite(void);

	void PrintText(string text,int x,int y,string font = "Arial Bold",int fontSize = 30,D3DCOLOR color = D3DCOLOR_XRGB(0,255,0));
	void PrintSprite(string filename,int x,int y,int width,int height,D3DCOLOR transcolor);

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	LPD3DXSPRITE spriteobj;

	//ÎÄ×Ö 
	LPD3DXFONT m_font;
	LPD3DXFONT MakeFont(string name, int size);
	void FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color = D3DCOLOR_XRGB(0,255,0));


	//¾«Áé
	LPDIRECT3DTEXTURE9 m_texture;
	LPDIRECT3DTEXTURE9 LoadTexture(string filename, D3DCOLOR transcolor);
	void Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, int x, int y, int width, int height, 
		int frame = 0, int columns = 1, float rotation = 0.0f, float scaleW = 1.0f, float scaleH = 1.0f, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));
	
};

