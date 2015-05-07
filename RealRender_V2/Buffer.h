#pragma once
#include "DeviceDx11.h"

//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
class Buffer
{
public:
	Buffer();
	virtual ~Buffer();

protected:
	ID3D11Buffer* m_pBuffer = nullptr;

public:
	virtual void CramBuffer() = 0;
	bool CreateBuffer(const void* pSysMem, UINT size, D3D11_USAGE usage, UINT bindFlags, UINT cpuAccessFlags, UINT miscFlags, UINT structureByteStride);
};
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
class VertexBuffer : public Buffer
{
public:
	VertexBuffer(UINT stride, UINT offset, UINT startSlot, UINT numbeffers);
	virtual ~VertexBuffer();

public:
	virtual void CramBuffer();

private:
	UINT m_stride;
	UINT m_offset;
	UINT m_startSlot;
	UINT m_numBuffers;
};
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
class IndexBuffer : public Buffer
{
public:
	IndexBuffer(DXGI_FORMAT format, UINT offset);
	virtual ~IndexBuffer();

public:
	virtual void CramBuffer();

private:
	DXGI_FORMAT m_format = DXGI_FORMAT_UNKNOWN;
	UINT m_offset = 0;
};
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式
class ConstantBuffer : public Buffer
{
public:
	enum SC_TYPE{ VSC = 1, PSC = 2, END };
public:
	ConstantBuffer(UINT startSlot, UINT numBuffers, int bitSelectedShader);
	virtual ~ConstantBuffer();

public:	
	virtual void UpdateBufferSubResource(const void* pscData);		
	virtual void CramBuffer();

protected:
	UINT m_startSlot = 0;
	UINT m_numBuffers = 0;
	int m_bitSelectedShader = 0;	
};
//式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式