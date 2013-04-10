#pragma once

#include "Header.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);

public:
	D3DXVECTOR3  g_vPos;
	D3DXVECTOR3  g_vViewAt;
	D3DXVECTOR3  g_vUp;
	float        g_vAngle;
};

