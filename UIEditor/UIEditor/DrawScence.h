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

	void SetWorldMatrix();//设置世界矩阵
	void SetViewProjectionMatrix();//设置投影矩阵
	void ProjCoorTransform();//投影坐标转换

	//bool isPointInPlane(Plane *plane);
	bool IsPointInPlan(PlaneData planData);
	bool UpdateUVData();
	void ScreenPointToProjPoint(CPoint point);
	
	void Render(CPoint movePoint,CPoint clickPoint);

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	Camera m_Camera;

	HWND m_hWnd;
	CPoint m_movePoint,m_clickPoint;
	PointToProj m_movePointProj,m_clickPointProj;

	Plane *m_backgrTexPlan;

	PlaneData sudokuPlanData;

	Sprite *m_sprite;

	CPoint m_lastPoint;
	bool m_DragFlag;
};

