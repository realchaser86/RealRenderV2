#pragma once
#include "DeviceDx11.h"

class DeviceResource;
class Shader;
class Object;
class Camera;
class CompositeObject;
class App
{
public:
	App();
	~App();	

public:
	bool Init( HWND hWnd );
	void Update(float dt);
	void Render();
	void CleanupApp();

private:
	bool CreateRenderTargetView();
	bool CreateDepthStencilView();

public:
	void OnKeyBoardInput(float dt);
	void SetMouseDelta(float dx, float dy);	
	
private:
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11DepthStencilView* m_pDepthStencilView;	
	Camera*				m_pCamera;
	CompositeObject*	m_pCompositeObject;
};