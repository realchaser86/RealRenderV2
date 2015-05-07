#pragma once

class BaseShader;
class ShaderStage
{
public:	
	~ShaderStage();
public:
	void AddShader(BaseShader* pShader);	
	void SetUpShaders();	

private:
	vector<BaseShader*> m_vShaders;
};
