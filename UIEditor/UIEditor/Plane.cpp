#include "stdafx.h"
#include "Plane.h"


Plane::Plane(LPDIRECT3DDEVICE9 pD3DDevice,HWND hWnd,PlaneData planeData)
{
	m_pd3dDevice = pD3DDevice;
	m_pBufferRec = NULL;
	m_hWnd = hWnd;
	m_planeData = planeData;
}


Plane::~Plane(void)
{
	m_pBufferRec->Release();
	m_pBufferRec = NULL;
}

HRESULT Plane::InitVB()
{
	
	PLANEVERTEX Vertices[] = 
	{
		{m_planeData.anchorPoint.x,					   m_planeData.anchorPoint.y - m_planeData.height,0.0f, D3DXCOLOR(1.0f,1.0f,1.0f,m_planeData.alpha),0.0f,1.0f},
		{m_planeData.anchorPoint.x,					   m_planeData.anchorPoint.y ,0.0f,						D3DXCOLOR(1.0f,1.0f,1.0f,m_planeData.alpha),0.0f,0.0f},
		{m_planeData.anchorPoint.x + m_planeData.width,m_planeData.anchorPoint.y - m_planeData.height,0.0f, D3DXCOLOR(1.0f,1.0f,1.0f,m_planeData.alpha),1.0f,1.0f},
		{m_planeData.anchorPoint.x + m_planeData.width,m_planeData.anchorPoint.y ,0.0f,						D3DXCOLOR(1.0f,1.0f,1.0f,m_planeData.alpha),1.0f,0.0f}
	};
	
	
	if(FAILED(m_pd3dDevice->CreateVertexBuffer(sizeof(Vertices)
		                                       ,0
											   ,D3DFVF_PLANEVERTEX
											   ,D3DPOOL_DEFAULT
											   ,&m_pBufferRec
											   ,NULL)))
	{
		return E_FAIL;
	}

	VOID*  pVertices;
	if(FAILED(m_pBufferRec->Lock(0, 
								 sizeof(Vertices),
								 (void**)&pVertices,
		                         0)))
	{
		return E_FAIL;
	}

	memcpy(pVertices,Vertices,sizeof(Vertices));
	m_pBufferRec->Unlock();

	return S_OK;
}

BOOL Plane::SetTexture(const char *FileTexture,int flag)
{
	if(FAILED(D3DXCreateTextureFromFile(m_pd3dDevice,FileTexture,&m_pTexScene[flag])))
	{
		return FALSE;
	}

	return TRUE;
}

void Plane::Render()
{
	m_pd3dDevice->SetStreamSource(0,m_pBufferRec,0,sizeof(PLANEVERTEX));
	m_pd3dDevice->SetFVF(D3DFVF_PLANEVERTEX);
	m_pd3dDevice->SetTexture(0,m_pTexScene[0]);
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}