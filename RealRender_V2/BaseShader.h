#pragma once
#include "ShaderStage.h"

class BaseShader
{
public:
	BaseShader(ShaderStage* pCollection)
	{
		pCollection->AddShader(this);
	}
	virtual ~BaseShader();

public:
	virtual bool Create(string shaderName, string entryPoint) = 0;
	virtual void SetupShader() = 0;	

public:
	bool BuildShader(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlob);
};

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
class VetexShader : public BaseShader
{
public:
	VetexShader(ShaderStage* pCollection);
	virtual ~VetexShader();
public:
	virtual bool Create(string shaderName, string entryPoint);
	virtual void SetupShader();

public:
	void AddLayoutFoam(const D3D11_INPUT_ELEMENT_DESC& desc);
	
private:
	ID3D11VertexShader*     m_pVertexShader = nullptr;
	ID3D11InputLayout*		m_pVertexLayout = nullptr;
	vector<D3D11_INPUT_ELEMENT_DESC> m_vLayoutFoam;
};
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
class PixelShader : public BaseShader
{
public:
	PixelShader(ShaderStage* pCollection);
	virtual ~PixelShader();
public:
	virtual bool Create(string shaderName, string entryPoint);
	virtual void SetupShader();	

private:
	ID3D11PixelShader*     m_pPixelShader = nullptr;
};
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式