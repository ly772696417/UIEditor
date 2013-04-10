#pragma once

#include "Header.h"

class Plane
{

public:
	Plane(LPDIRECT3DDEVICE9 pD3DDevice,HWND hWnd,PlaneData planeData);
	~Plane(void);

	HRESULT InitVB();
	BOOL SetTexture(const char *FileTexture,int flag);
	void Render();

private:
	LPDIRECT3DDEVICE9          m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9    m_pBufferRec;
	LPDIRECT3DTEXTURE9         m_pTexScene[2];

	HWND m_hWnd;

public:
	PlaneData m_planeData;
};

