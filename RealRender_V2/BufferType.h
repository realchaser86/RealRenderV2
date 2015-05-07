#pragma once
#include "stdafx.h"

struct P_Vertex
{
	XMFLOAT3 Pos;
};

struct PC_Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct PT_Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};

struct PN_Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
};

struct PNT_Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 Tex;
};
struct C_CBuffer
{
	XMFLOAT4 Color;
};
struct WVP_CBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};

struct WVPL_CBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
	XMFLOAT4 vLightDir;
	XMFLOAT4 vLightColor;	
};