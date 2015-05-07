#include "stdafx.h"
#include "BaseShader.h"
#include "STL_TemplateUtil.h"
#include "DeviceDx11.h"
#include "Global.h"

bool BaseShader::BuildShader(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlob)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )	
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlob, &pErrorBlob, NULL);

	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

		Safe_Release(pErrorBlob);

		return false;
	}

	Safe_Release(pErrorBlob);

	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return false;
	}

	return true;
}

BaseShader::~BaseShader()
{
}

bool VetexShader::Create(string shaderName, string entryPoint)
{
	wstring wShaderName(shaderName.begin(), shaderName.end());
	ID3DBlob* pVSBlob = nullptr;
	if (BuildShader(wShaderName.c_str(), entryPoint.c_str(), "vs_5_0", &pVSBlob))
	{		 
		if (SUCCEEDED(g_pDevicePack->GetDevice()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVertexShader)))
		{
			if (pVSBlob)
			{
				g_pDevicePack->GetDevice()->CreateInputLayout(&m_vLayoutFoam[0], m_vLayoutFoam.size(), pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pVertexLayout);
			}
			return true;
		}		
	}

	return false;
}

void VetexShader::SetupShader()
{	
	g_pDevicePack->GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	g_pDevicePack->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
	g_pDevicePack->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//Fix
}

void VetexShader::AddLayoutFoam(const D3D11_INPUT_ELEMENT_DESC& desc)
{
	m_vLayoutFoam.push_back(desc);
}

VetexShader::VetexShader(ShaderStage* pCollection) : BaseShader(pCollection){}

VetexShader::~VetexShader()
{
	Safe_Release(m_pVertexShader);
	Safe_Release(m_pVertexLayout);	
}

bool PixelShader::Create(string shaderName, string entryPoint)
{
	wstring wShaderName(shaderName.begin(), shaderName.end());
	ID3DBlob* pPSBlob = nullptr;
	if (BuildShader(wShaderName.c_str(), entryPoint.c_str(), "ps_5_0", &pPSBlob))
	{
		 
		if (SUCCEEDED(g_pDevicePack->GetDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_pPixelShader)))
		{
			return true;
		}
	}

	return false;
}

void PixelShader::SetupShader()
{
	 
	g_pDevicePack->GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
}

PixelShader::PixelShader(ShaderStage* pCollection) : BaseShader(pCollection){}

PixelShader::~PixelShader()
{
	Safe_Release(m_pPixelShader);
}
