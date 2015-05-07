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

	//�ӽ÷� ���� ����.
	ALIGNED16(CompositeObject);

private:
	XMFLOAT3 m_Pos = { 0, 0, 0 };
};