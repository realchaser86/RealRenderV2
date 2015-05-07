#pragma once
#include "stdafx.h"
#include "Macro.h"

class ObjectInfo
{
public:
	ObjectInfo();
	~ObjectInfo();
	ALIGNED16(ObjectInfo);

private:
	map<string, XMFLOAT4> m_MapFloat4;
	map<string, XMMATRIX> m_MapMatrix;

public:
	void UpdateFloat4(string name, const XMFLOAT4& float4);
	void UpdateMatrix(string name, const XMMATRIX& matrix);
public:
	XMFLOAT4 FindFloat4(string name);
	XMMATRIX FindMatrix(string name);
};

