#pragma once
#include "ComponentPart.h"
#include "BufferType.h"

class VertexBuffer;
class IndexBuffer;
class ComponentShape : public ComponentPart
{
public:
	ComponentShape(CompositeObject* pOwner);
	virtual ~ComponentShape();

public:
	void CreateBuffer();
	void CramBuffers();

protected:
	virtual bool CreateVertexBuffer() = 0;
	virtual bool CreateIndexBuffer() = 0;

protected:
	VertexBuffer* m_pVertexBuffer = nullptr;
	IndexBuffer* m_pIndexBuffer = nullptr;
};

class BoxShape : public ComponentShape
{
public:
	BoxShape(CompositeObject* pOwner);
	virtual ~BoxShape();
public:
	virtual void Init();

protected:
	virtual bool CreateVertexBuffer();
	virtual bool CreateIndexBuffer();

private:
	vector<P_Vertex> m_vVertices;
	vector<WORD> m_vIndices;
};

