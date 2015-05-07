#include "stdafx.h"
#include "ComponentShape.h"
#include "Buffer.h"
#include "STL_TemplateUtil.h"

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ComponentShape::ComponentShape(CompositeObject* pOwner) : ComponentPart(pOwner){}
ComponentShape::~ComponentShape()
{
	Safe_Delete(m_pVertexBuffer);
	Safe_Delete(m_pIndexBuffer);
}
void ComponentShape::CreateBuffer()
{
	assert(CreateVertexBuffer());
	assert(CreateIndexBuffer());
}

void ComponentShape::CramBuffers()
{
	assert(m_pVertexBuffer && m_pIndexBuffer);

	m_pVertexBuffer->CramBuffer();
	m_pIndexBuffer->CramBuffer();
}

BoxShape::BoxShape(CompositeObject* pOwner) : ComponentShape(pOwner){}
BoxShape::~BoxShape(){}
void BoxShape::Init()
{
	m_vVertices =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f) },	{ XMFLOAT3(1.0f, 1.0f, -1.0f) }, { XMFLOAT3(1.0f, 1.0f, 1.0f) }, 	{ XMFLOAT3(-1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f) }, { XMFLOAT3(1.0f, -1.0f, -1.0f) }, { XMFLOAT3(1.0f, -1.0f, 1.0f) }, { XMFLOAT3(-1.0f, -1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f) }, { XMFLOAT3(-1.0f, -1.0f, -1.0f) }, { XMFLOAT3(-1.0f, 1.0f, -1.0f) }, { XMFLOAT3(-1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f) }, { XMFLOAT3(1.0f, -1.0f, -1.0f) }, { XMFLOAT3(1.0f, 1.0f, -1.0f) }, { XMFLOAT3(1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f) }, { XMFLOAT3(1.0f, -1.0f, -1.0f) }, { XMFLOAT3(1.0f, 1.0f, -1.0f) }, { XMFLOAT3(-1.0f, 1.0f, -1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f) }, { XMFLOAT3(1.0f, -1.0f, 1.0f) }, { XMFLOAT3(1.0f, 1.0f, 1.0f) }, { XMFLOAT3(-1.0f, 1.0f, 1.0f) }
	};

	m_vIndices =
	{
		3, 1, 0, 2, 1, 3,
		6, 4, 5, 7, 4, 6,
		11, 9, 8, 10, 9, 11,
		14, 12, 13, 15, 12, 14,
		19, 17, 16,	18, 17, 19,
		22, 20, 21,	23, 20, 22
	};
}

bool BoxShape::CreateVertexBuffer()
{
	m_pVertexBuffer = new VertexBuffer(sizeof(P_Vertex), 0, 0, 1);
	int verticesSize = m_vVertices.size() * sizeof(P_Vertex);	
	return m_pVertexBuffer->CreateBuffer(&m_vVertices[0], verticesSize, D3D11_USAGE_IMMUTABLE, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0);
}

bool BoxShape::CreateIndexBuffer()
{
	m_pIndexBuffer = new IndexBuffer(DXGI_FORMAT_R16_UINT, 0);
	int indicessSize = m_vIndices.size() * sizeof(WORD);
	return m_pIndexBuffer->CreateBuffer(&m_vIndices[0], indicessSize, D3D11_USAGE_IMMUTABLE, D3D11_BIND_INDEX_BUFFER, 0, 0, 0);	
}
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式