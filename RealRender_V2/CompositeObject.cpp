#include "stdafx.h"
#include "CompositeObject.h"
#include "STL_TemplateUtil.h"
#include "ComponentShape.h"
#include "ComponentRender.h"
#include "Global.h"

CompositeObject::CompositeObject(){}
CompositeObject::~CompositeObject()
{
	Safe_Delete(m_pRender);
	Safe_Delete(m_pShape);
}

void CompositeObject::Init()
{
	assert( m_pShape && m_pRender );
	
	m_pShape->Init();
	m_pShape->CreateBuffer();
	
	m_pRender->Init();
	m_pRender->CreateBuffer();	
}

void CompositeObject::Update(float dt)
{	
	assert(m_pShape && m_pRender);	
	
	//나중에 월드용 업데이트만 따로 분리해서 동작 속성에따라 다른 world결과를 리턴하도록 하자
	m_pRender->UpdateObjectInfoMatrix("world", XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z));	
	m_pRender->UpdateObjectInfoMatrix("view", g_View);
	m_pRender->UpdateObjectInfoMatrix("projection", g_Projection);
	m_pRender->UpdateConstantBuffer();
}

void CompositeObject::Render()
{
	assert(m_pShape && m_pRender);
		
	m_pShape->CramBuffers();
	m_pRender->CramBuffers();

	m_pRender->Render();
	g_pDevicePack->GetDeviceContext()->DrawIndexed(36, 0, 0);
}

void CompositeObject::SetShape(ComponentShape* pShape)
{
	m_pShape = pShape;
}

void CompositeObject::SetRender(ComponentRender* pRender)
{
	m_pRender = pRender;
}

void CompositeObject::SetPos(XMFLOAT3 pos)
{
	m_Pos = pos;
}
