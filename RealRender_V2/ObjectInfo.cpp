#include "stdafx.h"
#include "ObjectInfo.h"

ObjectInfo::ObjectInfo()
{}

ObjectInfo::~ObjectInfo()
{}

void ObjectInfo::UpdateFloat4(string name, const XMFLOAT4& float4)
{
	m_MapFloat4[name] = float4;
}

void ObjectInfo::UpdateMatrix(string name, const XMMATRIX& matrix)
{
	m_MapMatrix[name] = matrix;
}

XMFLOAT4 ObjectInfo::FindFloat4(string name)
{
	auto iter = m_MapFloat4.find(name);
	if (iter == m_MapFloat4.end())
		assert(false);

	return iter->second;
}

XMMATRIX ObjectInfo::FindMatrix(string name)
{
	auto iter = m_MapMatrix.find(name);
	if (iter == m_MapMatrix.end())
		assert(false);

	return iter->second;
}
