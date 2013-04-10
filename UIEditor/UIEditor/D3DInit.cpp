#include "stdafx.h"
#include "D3DInit.h"


D3DInit::D3DInit(HWND hWnd)
{
	m_hWnd = hWnd;
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}


D3DInit::~D3DInit(void)
{
	m_pD3D->Release();
	m_pD3D = NULL;

	m_pD3DDevice->Release();
	m_pD3DDevice = NULL;
}

BOOL D3DInit::GameInit()
{
	if (SUCCEEDED(this->InitD3D()))
	{
		//scence process
		m_pDrawScence = new DrawScence(m_pD3DDevice,m_hWnd);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

HRESULT D3DInit::InitD3D(){
	if (!(m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	//得到窗口大小
	CRect rect;
	GetWindowRect(m_hWnd,&rect);

	D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.hDeviceWindow = m_hWnd;
	d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.EnableAutoDepthStencil = 1;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = rect.Width();
	d3dpp.BackBufferHeight = rect.Height();

    //create Direct3D device
	if (FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		MessageBox(m_hWnd,"创建设备失败！",NULL,NULL);
		return E_FAIL;
	}

	return S_OK;
}

void D3DInit::Render(CPoint movePoint,CPoint clickPoint)
{
	if (NULL == m_pD3DDevice)
	{
		return;
	}

	m_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255,255,255),1.0f,0);
	m_pD3DDevice->BeginScene();
	
	m_pDrawScence->Render(movePoint,clickPoint);

	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL,NULL,NULL,NULL);
}