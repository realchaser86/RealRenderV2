#pragma once
#include "ComponentPart.h"
#include "ShaderStage.h"
#include "ObjectInfo.h"

class ConstantBuffer;
class ComponentRender : public ComponentPart
{
public:
	ComponentRender(CompositeObject* pOwner);
	virtual ~ComponentRender();	

public:
	void CreateBuffer();
	bool UpdateConstantBufferSubResource(string key, void* pscData);
	void CramBuffers();
	void UpdateObjectInfoMatrix(string key, XMMATRIX& matrix);
	void UpdateObjectInfoFloat4(string key, XMFLOAT4& float4);

protected:
	virtual bool CreateConstantBuffer() = 0;

protected:
	virtual void SetupShaders() = 0;

public:	
	virtual void Render() = 0;
	virtual void UpdateConstantBuffer() =0;	

protected:
	ObjectInfo	m_Info;
	map<string, ConstantBuffer*> m_mConstantBuffers;
	ShaderStage m_ShaderStage;
};

class LightTextureRender : public ComponentRender
{
public:
	LightTextureRender(CompositeObject* pOwner);
	virtual ~LightTextureRender();

public:
	virtual bool CreateConstantBuffer();

protected:
	virtual void SetupShaders();

public:
	virtual void Init();
	virtual void Render();	
	virtual void UpdateConstantBuffer();
};

