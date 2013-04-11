#pragma once

#include "Header.h"
#include "Camera.h"
#include "Plane.h"

#include "Sprite.h"

#include <cstdlib>

typedef struct PointToProj
{
	float x;
	float y;
	float z;
}PointToProj;

class DrawScence
{
public:
	DrawScence(LPDIRECT3DDEVICE9 pD3DDevice,HWND hWnd);
	~DrawScence(void);

	void SetWorldMatrix();//�����������
	void SetViewProjectionMatrix();//����ͶӰ����
	void ProjCoorTransform();//ͶӰ����ת��

	bool isPointInPlane(Plane *plane);

	void Render(CPoint movePoint,CPoint clickPoint);

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	Camera m_Camera;

	HWND m_hWnd;
	CPoint m_movePoint,m_clickPoint;
	PointToProj m_movePointProj,m_clickPointProj;

	Plane *m_backgrTexPlan;
	Plane *m_sudokuTexPlan;

	Sprite *textSprite;
};

