#pragma once

#include "Header.h"
#include "DrawScence.h"

class D3DInit
{
public:
	D3DInit(HWND hWnd);
	~D3DInit(void);

	BOOL GameInit();
	HRESULT InitD3D();
	void Render(CPoint movePoint,CPoint clickPoint);

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	DrawScence *m_pDrawScence;
	HWND m_hWnd;
};

