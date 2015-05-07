#pragma once
#include "Singleton.h"

class Sampler
{
public:
	virtual void Initialize() = 0;
	virtual ~Sampler();	

protected:	
	ID3D11SamplerState* m_pSampler = nullptr;
};

class LinearSampler : public Sampler
{
public:
	virtual void Initialize();
};

class SamplerManager : public Singleton<SamplerManager>
{
	friend class Singleton<SamplerManager>;
private:
	SamplerManager() = default;
	SamplerManager(const SamplerManager&) = delete;
	SamplerManager& operator=(const SamplerManager&) = delete;

public:
	virtual ~SamplerManager();
	
public:
	void PrepareSampler();
	const Sampler* GetSampler(string samplerName);	

private:
	map<string, Sampler*> m_mSamplers;
};