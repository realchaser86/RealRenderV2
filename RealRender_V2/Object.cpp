#include "stdafx.h"
#include "Object.h"
#include "STL_TemplateUtil.h"
#include "DeviceDx11.h"
#include "BufferType.h"
#include "Shader.h"
#include "Global.h"
#include "SamplerManager.h"

Object::Object() :
m_pShader(nullptr)
, m_pConstantBuffer(nullptr)
, m_pVertexLayout(nullptr)
, m_pVertexBuffer(nullptr)
, m_pIndexBuffer(nullptr)
, m_pSamplerLinear(nullptr)
, m_pTextureRV(nullptr)
{}

Object::~Object()
{
	Clear();
}

bool Object::Init()
{
	m_World = XMMatrixIdentity();
	m_Pos = { 0.f, 0.f, 0.f };
	return true;
}

void Object::Clear()
{
	Safe_Release(m_pVertexLayout);
	Safe_Release(m_pVertexBuffer);
	Safe_Release(m_pIndexBuffer);
	Safe_Release(m_pConstantBuffer);
	Safe_Release(m_pSamplerLinear);
	Safe_Release(m_pTextureRV);
	Safe_Delete(m_pShader);
}

bool Object::CreateBuffer(const void* pSysMem, UINT size, D3D11_USAGE usage, UINT bindFlags, UINT cpuAccessFlags, UINT miscFlags, UINT structureByteStride, ID3D11Buffer** ppOutputBuffer)
{
	 
	D3D11_BUFFER_DESC bd;
	bd.Usage = usage;
	bd.ByteWidth = size;
	bd.BindFlags = bindFlags;
	bd.CPUAccessFlags = cpuAccessFlags;
	bd.MiscFlags = miscFlags;
	bd.StructureByteStride = structureByteStride;

	HRESULT hr;
	if (pSysMem)
	{
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = pSysMem;
		hr = g_pDevicePack->GetDevice()->CreateBuffer(&bd, &InitData, ppOutputBuffer);
	}
	else
	{
		hr = g_pDevicePack->GetDevice()->CreateBuffer(&bd, nullptr, ppOutputBuffer);
	}

	return SUCCEEDED(hr);
}

Box::Box()
{
}

Box::~Box()
{
	Clear();
}

bool Box::Init()
{
	 

	m_pShader = new Shader();
	if (m_pShader)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		UINT numElements = ARRAYSIZE(layout);

		{
			ID3DBlob* pVSBlob = nullptr;							 
			m_pShader->CreateVertexShader(g_pDevicePack->GetDevice(), L"LightTexture.fx", "VS", "vs_5_0", &pVSBlob);

			if (pVSBlob)
				g_pDevicePack->GetDevice()->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pVertexLayout);

			if (m_pVertexLayout)
				Safe_Release(pVSBlob);
			else
				return false;
		}

		{
			ID3DBlob* pPSBlob = nullptr;
			m_pShader->CreatePixelShader(g_pDevicePack->GetDevice(), L"LightTexture.fx", "PS", "ps_5_0", &pPSBlob);

			if (pPSBlob)
				Safe_Release(pPSBlob);
			else
				return false;
		}
	}

	vector<PNT_Vertex> vertices =	
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT2(0.0f, 0.0f)	},
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) 	},
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) 		},
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) 	},

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)	},
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) 	},
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),	XMFLOAT2(1.0f, 1.0f)	},
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) 	},

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) 	},
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f)	},
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) 	},
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f),	XMFLOAT2(0.0f, 1.0f)	},

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) 	},
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f)	},
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) 	},
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f)		},

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f)	},
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 0.0f)	},
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 1.0f)	},
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 1.0f)	},

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)	},
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)		},
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)		},
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT2(0.0f, 1.0f)		},
	};	

	vector<WORD> indices =
	{
		3, 1, 0,
		2, 1, 3,

		6, 4, 5,
		7, 4, 6,

		11, 9, 8,
		10, 9, 11,

		14, 12, 13,
		15, 12, 14,

		19, 17, 16,
		18, 17, 19,

		22, 20, 21,
		23, 20, 22
	};

	int totalVertexSize = vertices.size() * sizeof(PNT_Vertex);
	int totalIndexSize = indices.size() * sizeof(WORD);
	CreateBuffer(&vertices[0], totalVertexSize, D3D11_USAGE_IMMUTABLE, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0, &m_pVertexBuffer);
	CreateBuffer(&indices[0], totalIndexSize, D3D11_USAGE_IMMUTABLE, D3D11_BIND_INDEX_BUFFER, 0, 0, 0, &m_pIndexBuffer);
	CreateBuffer(nullptr, sizeof(WVPL_CBuffer), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0, &m_pConstantBuffer);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	g_pDevicePack->GetDevice()->CreateSamplerState(&sampDesc, &m_pSamplerLinear);

	if (m_pSamplerLinear == nullptr)
		return false;

	D3DX11CreateShaderResourceViewFromFile(g_pDevicePack->GetDevice(), L"seafloor.dds", NULL, NULL, &m_pTextureRV, NULL);
	if (m_pTextureRV == nullptr)
		return false;

	return true;
}

void Box::update(float dt)
{
	static float t = 0.0f;
	t += dt;

	m_World = XMMatrixRotationY(t) * XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);

	WVPL_CBuffer cb;
	cb.mWorld = XMMatrixTranspose(m_World);
	cb.mView = XMMatrixTranspose(g_View);
	cb.mProjection = XMMatrixTranspose(g_Projection);
	cb.vLightDir = XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f);
	cb.vLightColor = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);

	 
	g_pDevicePack->GetDeviceContext()->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);
}

void Box::Render()
{
	UINT stride = sizeof(PNT_Vertex);
	UINT offset = 0;

	 

	g_pDevicePack->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	g_pDevicePack->GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	g_pDevicePack->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
	g_pDevicePack->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	g_pDevicePack->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	g_pDevicePack->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	g_pDevicePack->GetDeviceContext()->VSSetShader(m_pShader->GetVertexShader(), NULL, 0);
	g_pDevicePack->GetDeviceContext()->PSSetShader(m_pShader->GetPixelShader(), NULL, 0);

	g_pDevicePack->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerLinear);
	g_pDevicePack->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTextureRV);

	g_pDevicePack->GetDeviceContext()->DrawIndexed(36, 0, 0);
}

void Box::Clear(){}

Sphere::Sphere()
:m_Radius(3), m_SliceCount(30), m_StackCount(30), m_IndexCount(0)
{}

Sphere::~Sphere()
{
	Clear();
}

bool Sphere::Init()
{
	m_pShader = new Shader();
	if (m_pShader)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		UINT numElements = ARRAYSIZE(layout);

		{
			ID3DBlob* pVSBlob = nullptr;
			m_pShader->CreateVertexShader(g_pDevicePack->GetDevice(), L"LightTexture.fx", "VS", "vs_5_0", &pVSBlob);

			if (pVSBlob)
				g_pDevicePack->GetDevice()->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pVertexLayout);

			if (m_pVertexLayout)
				Safe_Release(pVSBlob);
			else
				return false;
		}

		{
			ID3DBlob* pPSBlob = nullptr;
			m_pShader->CreatePixelShader(g_pDevicePack->GetDevice(), L"LightTexture.fx", "PS", "ps_5_0", &pPSBlob);

			if (pPSBlob)
				Safe_Release(pPSBlob);
			else
				return false;
		}
	}

	PNT_Vertex topVertex;
	topVertex.Pos = XMFLOAT3(0.0f, +m_Radius, 0.0f);
	topVertex.Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	topVertex.Tex = XMFLOAT2(1.0f, 0.0f);	

	PNT_Vertex bottomVertex;
	bottomVertex.Pos = XMFLOAT3(0.0f, -m_Radius, 0.0f);
	bottomVertex.Normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	bottomVertex.Tex = XMFLOAT2(1.0f, 0.0f);	

	vector<PNT_Vertex> vertices;
	vertices.push_back(topVertex);
	float phiStep = XM_PI / m_StackCount;
	float thetaStep = 2.0f*XM_PI / m_SliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (int i = 1; i <= m_StackCount - 1; ++i)
	{
		float phi = i*phiStep;

		// Vertices of ring.
		for (int j = 0; j <= m_SliceCount; ++j)
		{
			float theta = j*thetaStep;

			PNT_Vertex v;

			// spherical to cartesian
			v.Pos.x = m_Radius*sinf(phi)*cosf(theta);
			v.Pos.y = m_Radius*cosf(phi);
			v.Pos.z = m_Radius*sinf(phi)*sinf(theta);
			v.Normal = XMFLOAT3(0, 0, 0);
			
			XMVECTOR p = XMLoadFloat3(&v.Pos);
			XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

			v.Tex.x = theta / XM_2PI;
			v.Tex.y = phi / XM_PI;

			vertices.push_back(v);
		}
	}	

	for (UINT i = 0; i < vertices.size(); ++i)
	{
		XMStoreFloat3(&vertices[i].Normal, XMVector3Normalize(XMLoadFloat3(&vertices[i].Normal)));
	}

	//--------------------------------------------------------------------
	vector<WORD> indices;
	for (int i = 1; i <= m_SliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	int baseIndex = 1;
	int ringVertexCount = m_SliceCount + 1;
	for (int i = 0; i < m_StackCount - 2; ++i)
	{
		for (int j = 0; j < m_SliceCount; ++j)
		{
			indices.push_back(baseIndex + i*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	int southPoleIndex = (int)vertices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for (int i = 0; i < m_SliceCount; ++i)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}
	
	const int numTriangles = (m_StackCount * m_SliceCount) + ((m_StackCount - 2) * m_SliceCount);
	for (int i = 0; i < numTriangles; ++i)
	{
		int i0 = indices[i * 3 + 0];
		int i1 = indices[i * 3 + 1];
		int i2 = indices[i * 3 + 2];

		XMVECTOR v0 = XMLoadFloat3(&vertices[i0].Pos);
		XMVECTOR v1 = XMLoadFloat3(&vertices[i1].Pos);
		XMVECTOR v2 = XMLoadFloat3(&vertices[i2].Pos);

		XMVECTOR e0 = XMVectorSubtract(v1, v0);
		XMVECTOR e1 = XMVectorSubtract(v2, v0);
		XMVECTOR  faceNormal = XMVector3Cross(e0, e1);

		XMVECTOR normal = XMLoadFloat3(&vertices[i0].Normal);
		XMStoreFloat3(&vertices[i0].Normal, XMVectorAdd(normal, faceNormal));

		normal = XMLoadFloat3(&vertices[i1].Normal);
		XMStoreFloat3(&vertices[i1].Normal, XMVectorAdd(normal, faceNormal));

		normal = XMLoadFloat3(&vertices[i2].Normal);
		XMStoreFloat3(&vertices[i2].Normal, XMVectorAdd(normal, faceNormal));
	}
	
	//-----------------------------------------------------------------
	int totalVertexSize = vertices.size() * sizeof(PNT_Vertex);
	int totalIndexSize = indices.size() * sizeof(WORD);
	m_IndexCount = indices.size();

	CreateBuffer(&vertices[0], totalVertexSize, D3D11_USAGE_IMMUTABLE, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0, &m_pVertexBuffer);
	CreateBuffer(&indices[0], totalIndexSize, D3D11_USAGE_IMMUTABLE, D3D11_BIND_INDEX_BUFFER, 0, 0, 0, &m_pIndexBuffer);
	CreateBuffer(nullptr, sizeof(WVPL_CBuffer), D3D11_USAGE_DEFAULT, D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0, &m_pConstantBuffer);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	g_pDevicePack->GetDevice()->CreateSamplerState(&sampDesc, &m_pSamplerLinear);

	if (m_pSamplerLinear == nullptr)
		return false;

	D3DX11CreateShaderResourceViewFromFile(g_pDevicePack->GetDevice(), L"seafloor.dds", NULL, NULL, &m_pTextureRV, NULL);
	if (m_pTextureRV == nullptr)
		return false;

	return true;
}

void Sphere::update(float dt)
{
	static float t = 0.0f;
	t += dt;

	m_World = XMMatrixRotationY(t) * XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);

	WVPL_CBuffer cb;
	cb.mWorld = XMMatrixTranspose(m_World);
	cb.mView = XMMatrixTranspose(g_View);
	cb.mProjection = XMMatrixTranspose(g_Projection);
	cb.vLightDir = XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f);
	cb.vLightColor = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	
	g_pDevicePack->GetDeviceContext()->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);
}

void Sphere::Render()
{
	UINT stride = sizeof(PNT_Vertex);
	UINT offset = 0;	

	g_pDevicePack->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	g_pDevicePack->GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	g_pDevicePack->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
	g_pDevicePack->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	g_pDevicePack->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	g_pDevicePack->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	g_pDevicePack->GetDeviceContext()->VSSetShader(m_pShader->GetVertexShader(), NULL, 0);
	g_pDevicePack->GetDeviceContext()->PSSetShader(m_pShader->GetPixelShader(), NULL, 0);

	g_pDevicePack->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerLinear);
	g_pDevicePack->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTextureRV);

	g_pDevicePack->GetDeviceContext()->DrawIndexed(m_IndexCount, 0, 0);
}

void Sphere::Clear()
{
}
