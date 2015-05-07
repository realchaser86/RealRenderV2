#pragma once
#include "ComponentRender.h"

class ColorRender : public ComponentRender
{
public:
	ColorRender(CompositeObject* pOwner);
	virtual ~ColorRender();

public:
	virtual bool CreateConstantBuffer();

protected:
	virtual void SetupShaders();

public:
	virtual void Init();
	virtual void Render();
	virtual void UpdateConstantBuffer();
};