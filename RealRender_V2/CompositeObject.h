#pragma once
#include "Macro.h"
#include "Buffer.h"

class ComponentRender;
class ComponentShape;
class CompositeObject
{
public:
	CompositeObject();
	~CompositeObject();

private:
	ComponentShape*		m_pShape = nullptr;
	ComponentRender*	m_pRender = nullptr;	

public:
	void SetShape(ComponentShape* pShape);
	void SetRender(ComponentRender* pRender);
	void SetPos(XMFLOAT3 pos);	

public:
	void Init();
	void Update(float dt);
	void Render();

	//임시로 만들어서 쓴다.
	ALIGNED16(CompositeObject);

private:
	XMFLOAT3 m_Pos = { 0, 0, 0 };
};