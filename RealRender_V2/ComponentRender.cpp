#include "stdafx.h"
#include "ComponentRender.h"
#include "BufferType.h"
#include "STL_TemplateUtil.h"
#include "BaseShader.h"
#include "DeviceDx11.h"
#include "Buffer.h"

ComponentRender::ComponentRender(CompositeObject* pOwner) : ComponentPart(pOwner){}
ComponentRender::~ComponentRender()
{
	Safe_Delete_Map(m_mConstantBuffers);
}

void ComponentRender::CreateBuffer()
{
	assert( CreateConstantBuffer() );
}

void ComponentRender::CramBuffers()
{
	auto iter = m_mConstantBuffers.begin();
	while (iter != m_mConstantBuffers.end())
	{
		iter->second->CramBuffer();
		++iter;
	}
}

bool ComponentRender::UpdateConstantBufferSubResource(string key, void* pscData)
{
	auto iter = m_mConstantBuffers.find(key);
	if (iter != m_mConstantBuffers.end())
	{
		iter->second->UpdateBufferSubResource(pscData);
		return true;
	}

	return false;
}

void ComponentRender::UpdateObjectInfoMatrix(string key, XMMATRIX& matrix)
{
	m_Info.UpdateMatrix(key, matrix);
}

void ComponentRender::UpdateObjectInfoFloat4(string key, XMFLOAT4& float4)
{
	m_Info.UpdateFloat4(key, float4);
}

LightTextureRender::LightTextureRender(CompositeObject* pOwner) : ComponentRender(pOwner){}
LightTextureRender::~LightTextureRender(){}
void LightTextureRender::Init(){}
void LightTextureRender::Render(){}
bool LightTextureRender::CreateConstantBuffer(){ return true; }
void LightTextureRender::UpdateConstantBuffer(){}
void LightTextureRender::SetupShaders(){}
