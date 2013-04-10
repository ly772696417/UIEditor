#include "stdafx.h"
#include "Camera.h"


Camera::Camera(void)
{
	D3DXVECTOR3  m_vPos(0.0, 0.0, -10.0);
	D3DXVECTOR3  m_vViewAt(0.0, 0.0, 0.0);
	D3DXVECTOR3  m_vUp(0.0, 1.0, 0.0);

	g_vPos      =  m_vPos;
	g_vViewAt   =  m_vViewAt;
	g_vUp       =  m_vUp;
	g_vAngle    =  0;
}


Camera::~Camera(void)
{
}
