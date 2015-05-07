#include "stdafx.h"
#include "ComponentPart.h"

ComponentPart::ComponentPart(CompositeObject* pOwner) 
: m_pOwner(pOwner)
{
}

ComponentPart::~ComponentPart()
{
	m_pOwner = nullptr;
}

CompositeObject* ComponentPart::GetOwner()
{
	return m_pOwner;
}
