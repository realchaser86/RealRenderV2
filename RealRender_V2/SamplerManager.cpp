#include "stdafx.h"
#include "SamplerManager.h"
#include "STL_TemplateUtil.h"
#include "DeviceDx11.h"
#include "Global.h"

SamplerManager::~SamplerManager()
{
	Safe_Delete_Map(m_mSamplers);
}

void SamplerManager::PrepareSampler()
{	
	m_mSamplers.insert({ "LinearSampler", new LinearSampler() });
}

const Sampler* SamplerManager::GetSampler(string samplerName)
{
	auto iter = m_mSamplers.find(samplerName);
	if (iter != m_mSamplers.end())
	{
		return iter->second;
	}

	return nullptr;
}

void LinearSampler::Initialize()
{
	 

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = g_pDevicePack->GetDevice()->CreateSamplerState(&sampDesc, &m_pSampler);	

	assert(SUCCEEDED(hr));
}

Sampler::~Sampler()
{
	Safe_Release(m_pSampler);
}
