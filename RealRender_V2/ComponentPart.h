#pragma once

class CompositeObject;
class ComponentPart
{
public:
	ComponentPart(CompositeObject* pOwner);
	virtual ~ComponentPart();

public:
	virtual void Init() = 0;		
	virtual void CreateBuffer() = 0;
	virtual void CramBuffers() = 0;

public:
	CompositeObject* GetOwner();

protected:
	CompositeObject* m_pOwner;
};