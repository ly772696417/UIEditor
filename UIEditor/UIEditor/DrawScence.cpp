#include "stdafx.h"
#include "DrawScence.h"


DrawScence::DrawScence(LPDIRECT3DDEVICE9 pD3DDevice,HWND hWnd)
{
	m_pD3DDevice = pD3DDevice;
	m_hWnd = hWnd;

	//background texture
	PlaneData backPlanData;
	backPlanData.alpha = 1.0f;
	backPlanData.anchorPoint = CPoint(-5.0f,-5.0f);
	backPlanData.height = 10.0f;
	backPlanData.width = 10.0f;

	m_backgrTexPlan = new Plane(m_pD3DDevice,m_hWnd,backPlanData);
	m_backgrTexPlan->InitVB();
	m_backgrTexPlan->SetTexture("pic\\back.bmp",0);
	m_backgrTexPlan->SetTexture("pic\\back.bmp",1);

	
	//sudoku texture
	sudokuPlanData.alpha = 0.1f;
	sudokuPlanData.anchorPoint = CPoint(200.0f,200.0f);
	sudokuPlanData.height = 100.0f;
	sudokuPlanData.width = 100.0f;
	
	//文字精灵对象的创建
	m_sprite = new Sprite(m_pD3DDevice);
}


DrawScence::~DrawScence(void)
{
}

void DrawScence::SetWorldMatrix()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);
}

void DrawScence::SetViewProjectionMatrix()
{
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
					   &m_Camera.g_vPos,
					   &m_Camera.g_vViewAt,
					   &m_Camera.g_vUp);
	m_pD3DDevice->SetTransform(D3DTS_VIEW,&matView);

	CRect rect;
	GetWindowRect(m_hWnd,&rect);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
							   D3DX_PI * 0.5,
							   1.0f * rect.Width() / rect.Height(),
							   1.0f,
							   10000.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION,&matProj);

}

void DrawScence::ProjCoorTransform()
{
	D3DVIEWPORT9 vp;
	m_pD3DDevice->GetViewport(&vp);

	D3DXMATRIX mProj;
	m_pD3DDevice->GetTransform(D3DTS_PROJECTION,&mProj);

	m_movePointProj.x = (((2.0f * m_movePoint.x)/vp.Width) - 1.0f)/mProj(0,0);
	m_movePointProj.y = (((-2.0f * m_movePoint.y)/vp.Height) + 1.0f)/mProj(1,1);
	m_movePointProj.z = 1;

	m_clickPointProj.x = (((2.0f * m_clickPoint.x)/vp.Width) - 1.0f)/mProj(0,0);
	m_clickPointProj.y = (((-2.0f * m_clickPoint.y)/vp.Height) + 1.0f)/mProj(1,1);;
	m_clickPointProj.z = 1;

	
	CString str;
	str.AppendFormat("%f,%f",m_movePointProj.x,m_movePointProj.y);
	m_sprite->PrintText(str.GetString(),100,200);

	CString str1;
	str1.AppendFormat("%d,%d",m_clickPoint.x,m_clickPoint.y);
	m_sprite->PrintText(str1.GetString(),100,300);
}

bool DrawScence::IsPointInPlan(PlaneData planData)
{
	
	if (m_clickPoint.x != -1 || m_clickPoint.y != -1)
	{
		if (planData.anchorPoint.x < m_movePoint.x && 
			planData.anchorPoint.x + planData.width > m_movePoint.x && 
			planData.anchorPoint.y < m_movePoint.y && 
			planData.anchorPoint.y + planData.height > m_movePoint.y)
		{
			Beep(2000,200);
			return true;
		}
	}
	

	return false;
}

/*
bool DrawScence::isPointInPlane(Plane *plane)
{
	
	if (m_clickPoint.x != -1)
	{
		if ((m_clickPointProj.x * fabs(m_Camera.g_vPos.z) > plane->m_planeData.anchorPoint.x) &&
			(m_clickPointProj.x * fabs(m_Camera.g_vPos.z) < plane->m_planeData.anchorPoint.x + plane->m_planeData.width) &&
			(m_clickPointProj.y * fabs(m_Camera.g_vPos.z) > plane->m_planeData.anchorPoint.y) &&
			(m_clickPointProj.y * fabs(m_Camera.g_vPos.z) < plane->m_planeData.anchorPoint.y + plane->m_planeData.height)
			)
		{

		}
		

	}

	return false;
}
*/

void DrawScence::Render(CPoint movePoint,CPoint clickPoint)
{
	m_clickPoint = clickPoint;
	m_movePoint = movePoint;


	CString str;
	str.AppendFormat("%d,%d",m_movePoint.x,m_movePoint.y);
	m_sprite->PrintText(str.GetString(),100,100);

	m_sprite->PrintSprite("pic\\back.bmp",sudokuPlanData.anchorPoint.x,sudokuPlanData.anchorPoint.y,sudokuPlanData.width,sudokuPlanData.height,D3DCOLOR_XRGB(255,255,255));


	SetWorldMatrix();
	SetViewProjectionMatrix();

	ProjCoorTransform();

	IsPointInPlan(sudokuPlanData);

	m_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);

	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,false);
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTALPHA);

	m_backgrTexPlan->Render();
	//m_sudokuTexPlan->Render();

	//isPointInPlane(m_sudokuTexPlan);
}