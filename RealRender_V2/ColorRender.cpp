#include "stdafx.h"
#include "ColorRender.h"
#include "BaseShader.h"
#include "Buffer.h"
#include "BufferType.h"
#include "ObjectInfo.h"

ColorRender::ColorRender(CompositeObject* pOwner) : ComponentRender(pOwner){}
ColorRender::~ColorRender(){}

void ColorRender::Init()
{
	VetexShader* vs = new VetexShader(&m_ShaderStage);
	vs->AddLayoutFoam({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	vs->AddLayoutFoam({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	vs->AddLayoutFoam({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	vs->Create("color.fx", "VS");

	PixelShader* ps = new PixelShader(&m_ShaderStage);
	ps->Create("color.fx", "PS");

	m_Info.UpdateFloat4("color", XMFLOAT4{ 1, 1, 0, 1 });
}

void ColorRender::Render()
{
	SetupShaders();
}

bool ColorRender::CreateConstantBuffer()
{	
	bool isResult = true;
	
	ConstantBuffer* pConstantBuffer = new ConstantBuffer(0, 1, ConstantBuffer::VSC | ConstantBuffer::PSC);
	isResult = pConstantBuffer->CreateBuffer(nullptr, sizeof(WVP_CBuffer), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0);
	m_mConstantBuffers.insert({ "WVP_CBuffer", pConstantBuffer });

	pConstantBuffer = nullptr;
	pConstantBuffer = new ConstantBuffer(1, 1, ConstantBuffer::PSC);
	isResult = pConstantBuffer->CreateBuffer(nullptr, sizeof(C_CBuffer), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0);
	m_mConstantBuffers.insert({ "C_CBuffer", pConstantBuffer });

	return isResult;
}

void ColorRender::UpdateConstantBuffer()
{
	bool isResult = true;

	WVP_CBuffer wvp_cb;
	wvp_cb.mWorld = XMMatrixTranspose(m_Info.FindMatrix("world"));
	wvp_cb.mView = XMMatrixTranspose(m_Info.FindMatrix("view"));
	wvp_cb.mProjection = XMMatrixTranspose(m_Info.FindMatrix("projection"));
	isResult = UpdateConstantBufferSubResource("WVP_CBuffer", &wvp_cb);
	assert(isResult);
		
	C_CBuffer c_cb;
	c_cb.Color = m_Info.FindFloat4("color");
	isResult = UpdateConstantBufferSubResource("C_CBuffer", &c_cb);	
	assert(isResult);
}

void ColorRender::SetupShaders()
{
	m_ShaderStage.SetUpShaders();
}
