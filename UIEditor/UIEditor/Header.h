#pragma once

#include<iostream>

//D3DÍ·ÎÄ¼þ
#include<d3d9.h>
#include<d3dx9.h>

//D3D lib¿â
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

struct PLANEVERTEX
{
	FLOAT  x,y,z;
	DWORD  color;
	FLOAT  tu,tv;
};

#define D3DFVF_PLANEVERTEX  (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

typedef struct PlaneData
{
	CPoint anchorPoint;
	float width;
	float height;
	float alpha;

	PlaneData& operator=(const PlaneData& rhs)
	{
		anchorPoint = rhs.anchorPoint;
		width = rhs.width;
		height = rhs.height;
		alpha = rhs.alpha;

		return *this;
	}
};