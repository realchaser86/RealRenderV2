#pragma once
#include "Define.h"
#include "Macro.h"

class Shader;
class Object
{
public:
	Object();
	virtual ~Object();
	ALIGNED16(Object);

public:
	virtual bool Init();
	virtual void update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Clear();

public:
	inline XMMATRIX& GetWorldMaxtrix(){ return m_World; }
	inline void SetPos(XMFLOAT3& pos){ m_Pos = pos; }

protected:
	bool CreateBuffer(const void* pSysMem, UINT size, D3D11_USAGE usage, UINT bindFlags, UINT cpuAccessFlags, UINT miscFlags, UINT structureByteStride, ID3D11Buffer** ppOutputBuffer);

protected:
	Shader*						m_pShader;
	ID3D11InputLayout*			m_pVertexLayout;
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11Buffer*				m_pIndexBuffer;
	ID3D11Buffer*				m_pConstantBuffer;
	ID3D11SamplerState*			m_pSamplerLinear;		
	ID3D11ShaderResourceView*	m_pTextureRV;

	XMFLOAT3 m_Pos;
	XMMATRIX m_World;
};

class Box : public Object
{
public:
	Box();
	virtual ~Box();
	ALIGNED16(Box);

public:
	virtual bool Init();
	virtual void update(float dt);
	virtual void Render();
	virtual void Clear();
};

class Sphere : public Object
{
public:
	Sphere();
	virtual ~Sphere();
	ALIGNED16(Sphere);

public:
	virtual bool Init();
	virtual void update(float dt);
	virtual void Render();
	virtual void Clear();

private:
	float	m_Radius;
	int		m_SliceCount;
	int		m_StackCount;
	int		m_IndexCount;
};
