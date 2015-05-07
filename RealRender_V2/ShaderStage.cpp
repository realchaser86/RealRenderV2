#include "stdafx.h"
#include "ShaderStage.h"
#include "BaseShader.h"
#include "STL_TemplateUtil.h"

void ShaderStage::AddShader(BaseShader* pShader)
{
	m_vShaders.push_back(pShader);
}

void ShaderStage::SetUpShaders()
{
	for each (auto shader in m_vShaders)
	{
		shader->SetupShader();
	}
}

ShaderStage::~ShaderStage()
{
	Safe_Delete_VecList(m_vShaders);
}
