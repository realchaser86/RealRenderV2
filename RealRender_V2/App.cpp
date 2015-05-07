#include "stdafx.h"
#include "App.h"
#include "STL_TemplateUtil.h"
#include "DeviceResource.h"
#include "Shader.h"
#include "Const.h"
#include "BufferType.h"
#include "Global.h"
#include "Object.h"
#include "Camera.h"
#include "CompositeObject.h"
//
#include "ComponentShape.h"
#include "ColorRender.h"
//

DeviceDx11* g_pDevicePack = nullptr;
XMMATRIX    g_View;
XMMATRIX	g_Projection;

App::App() :
m_pCamera(nullptr)
{
}

App::~App()
{	
	CleanupApp();
}

bool App::Init( HWND hWnd )
{	
	g_pDevicePack = DeviceDx11::GetInstance();

	if (g_pDevicePack->InitDevice(hWnd))
		return false;
	
	if (!CreateRenderTargetView())
		return false;
	
	if (!CreateDepthStencilView())
		return false;

	g_pDevicePack->GetDeviceContext()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	D3D11_VIEWPORT screenViewport;
	screenViewport.TopLeftX = 0;
	screenViewport.TopLeftY = 0;
	screenViewport.Width = static_cast<float>(WINDOW_WIDTH);
	screenViewport.Height = static_cast<float>(WINDOW_HEIGHT);
	screenViewport.MinDepth = 0.0f;
	screenViewport.MaxDepth = 1.0f;
	g_pDevicePack->GetDeviceContext()->RSSetViewports(1, &screenViewport);

	m_pCamera = new Camera();	
	m_pCamera->SetPosition(0.0f, 0.0f, -30.0f);
	m_pCamera->SetLens(0.25f * PI, static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.01f, 3000.0f);		
	
	m_pCompositeObject = new CompositeObject();
	m_pCompositeObject->SetShape(new BoxShape(m_pCompositeObject));
	m_pCompositeObject->SetRender(new ColorRender(m_pCompositeObject));
	m_pCompositeObject->Init();	

	return true;
}

void App::Update(float dt)
{
	OnKeyBoardInput(dt);

	m_pCamera->UpdateViewMatrix();
	g_View = m_pCamera->View();
	g_Projection = m_pCamera->Proj();

	m_pCompositeObject->Update(dt);
}

void App::Render()
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	g_pDevicePack->GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	g_pDevicePack->GetDeviceContext()->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	m_pCompositeObject->Render();

	g_pDevicePack->GetSwapChain()->Present(0, 0);
}

void App::CleanupApp()
{		
	Safe_Release(m_pRenderTargetView);
	Safe_Release(m_pDepthStencilView);		
	Safe_Delete(m_pCompositeObject);
	Safe_Delete(m_pCamera);
}

bool App::CreateRenderTargetView()
{	
	ID3D11Texture2D* pBackBuffer = nullptr;
	g_pDevicePack->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	g_pDevicePack->GetDevice()->CreateRenderTargetView(pBackBuffer, 0, &m_pRenderTargetView);
	
	if (pBackBuffer && m_pRenderTargetView)
	{
		pBackBuffer->Release();
		return true;
	}	
	
	return false;	
}

bool App::CreateDepthStencilView()
{
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = WINDOW_WIDTH;
	depthStencilDesc.Height = WINDOW_HEIGHT;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencilBuffer = nullptr;
	g_pDevicePack->GetDevice()->CreateTexture2D(&depthStencilDesc, 0, &pDepthStencilBuffer);
	g_pDevicePack->GetDevice()->CreateDepthStencilView(pDepthStencilBuffer, 0, &m_pDepthStencilView);
	
	if (pDepthStencilBuffer && m_pDepthStencilView)
	{
		pDepthStencilBuffer->Release();
		return true;
	}	
	
	return false;	
}

void App::OnKeyBoardInput(float dt)
{
	if (!m_pCamera)
		return;

	if (GetAsyncKeyState('W') & 0x8000)
		m_pCamera->Walk(10.0f*dt);

	if (GetAsyncKeyState('S') & 0x8000)
		m_pCamera->Walk(-10.0f*dt);

	if (GetAsyncKeyState('A') & 0x8000)
		m_pCamera->Strafe(-10.0f*dt);

	if (GetAsyncKeyState('D') & 0x8000)
		m_pCamera->Strafe(10.0f*dt);
}

void App::SetMouseDelta(float dx, float dy)
{
	if (!m_pCamera)
		return;

	m_pCamera->Pitch(dy);
	m_pCamera->RotateY(dx);
}
