#include "stdafx.h"
#include "Buffer.h"
#include "Global.h"
#include "STL_TemplateUtil.h"

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
Buffer::Buffer(){}
Buffer::~Buffer()
{
	Safe_Release(m_pBuffer);
}

bool Buffer::CreateBuffer(const void* pSysMem, UINT size, D3D11_USAGE usage, UINT bindFlags, UINT cpuAccessFlags, UINT miscFlags, UINT structureByteStride)
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
	{	//v, p
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = pSysMem;
		hr = g_pDevicePack->GetDevice()->CreateBuffer(&bd, &InitData, &m_pBuffer);
	}
	else
	{	//c
		hr = g_pDevicePack->GetDevice()->CreateBuffer(&bd, nullptr, &m_pBuffer);
	}

	return SUCCEEDED(hr);
}

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
VertexBuffer::VertexBuffer(UINT stride, UINT offset, UINT startSlot, UINT numbeffers) 
: m_stride(stride), 
m_offset(offset), 
m_startSlot(startSlot), 
m_numBuffers(numbeffers)
{}

VertexBuffer::~VertexBuffer(){}
void VertexBuffer::CramBuffer()
{
	if (m_pBuffer)
	{		
		g_pDevicePack->GetDeviceContext()->IASetVertexBuffers(m_startSlot, m_numBuffers, &m_pBuffer, &m_stride, &m_offset);
	}	
}
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
IndexBuffer::IndexBuffer(DXGI_FORMAT format, UINT offset)
: m_format(format),
m_offset(offset)
{}
IndexBuffer::~IndexBuffer(){}

void IndexBuffer::CramBuffer()
{
	if (m_pBuffer)
	{
		g_pDevicePack->GetDeviceContext()->IASetIndexBuffer(m_pBuffer, m_format, m_offset);
	}
}
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
ConstantBuffer::ConstantBuffer(UINT startSlot, UINT numBuffers, int bitSelectedShader)
: m_startSlot(startSlot),
m_numBuffers(numBuffers),
m_bitSelectedShader(bitSelectedShader)
{}
ConstantBuffer::~ConstantBuffer(){}

void ConstantBuffer::UpdateBufferSubResource(const void* pscData)
{
	g_pDevicePack->GetDeviceContext()->UpdateSubresource(m_pBuffer, 0, NULL, pscData, 0, 0);
}

void ConstantBuffer::CramBuffer()
{
	if (m_bitSelectedShader & VSC)
		g_pDevicePack->GetDeviceContext()->VSSetConstantBuffers(m_startSlot, m_numBuffers, &m_pBuffer);
	
	if (m_bitSelectedShader & PSC)
		g_pDevicePack->GetDeviceContext()->PSSetConstantBuffers(m_startSlot, m_numBuffers, &m_pBuffer);

	//...
}



//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式