#include "stdafx.h"
#include "DeviceResource.h"
#include "STL_TemplateUtil.h"


DeviceResource::DeviceResource( ) 
: m_pRenderTargetView( nullptr ), m_pDepthStencilView( nullptr ),
  m_pVertexLayout( nullptr ),
  m_pVertexBuffer( nullptr ), m_pIndexBuffer( nullptr )
{
}

DeviceResource::~DeviceResource()
{	
	CleanupResource();
}

bool DeviceResource::CreateRenderTargetView( ID3D11Device* pDevice, IDXGISwapChain* pSwapChain )
{
	if( pDevice && pSwapChain )
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		if( SUCCEEDED( pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast< void** >( &pBackBuffer ) ) )
			&& SUCCEEDED( pDevice->CreateRenderTargetView( pBackBuffer, 0, &m_pRenderTargetView ) ) )
		{
			pBackBuffer->Release();
			return true;
		}	
	}
	return false;
}

bool DeviceResource::CreateDepthStencilView( ID3D11Device* pDevice, int width, int height )
{
	if( pDevice )
	{
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
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
		if (SUCCEEDED(pDevice->CreateTexture2D(&depthStencilDesc, 0, &pDepthStencilBuffer))
			&& SUCCEEDED(pDevice->CreateDepthStencilView(pDepthStencilBuffer, 0, &m_pDepthStencilView)))
		{
			pDepthStencilBuffer->Release();
			return true;
		}
	}

	return false;
}

void DeviceResource::InitViewport( int width, int height )
{
	m_ScreenViewport.TopLeftX = 0;
	m_ScreenViewport.TopLeftY = 0;
	m_ScreenViewport.Width = static_cast< float >( width );
	m_ScreenViewport.Height = static_cast< float >( height );
	m_ScreenViewport.MinDepth = 0.0f;
	m_ScreenViewport.MaxDepth = 1.0f;
}

void DeviceResource::CleanupResource()
{
	Safe_Release( m_pRenderTargetView );
	Safe_Release( m_pDepthStencilView );	
	
	Safe_Release( m_pVertexLayout );
	Safe_Release( m_pVertexBuffer );
	Safe_Release( m_pIndexBuffer );	
}

bool DeviceResource::CreateInputLayout( ID3D11Device* pDevice, const D3D11_INPUT_ELEMENT_DESC* pLayout, UINT numElements, ID3DBlob* pVSBlob )
{
	if( pDevice && pVSBlob && pLayout &&
		SUCCEEDED( pDevice->CreateInputLayout( pLayout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pVertexLayout ) ) )
	{
		return true;
	}	
	
	return false;
}

bool DeviceResource::CreateVertexBuffer( ID3D11Device* pDevice, int totalVertexSize, void* pVertices )
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof( bd ) );
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.ByteWidth = totalVertexSize;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof( InitData ) );
	InitData.pSysMem = pVertices;

	HRESULT hr = pDevice->CreateBuffer( &bd, &InitData, &m_pVertexBuffer );
	
	return SUCCEEDED( hr );	
}

bool DeviceResource::CreateIndexBuffer( ID3D11Device* pDevice, int totalIndexSize, void* pIndices )
{
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = totalIndexSize;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pIndices;
	HRESULT hr = pDevice->CreateBuffer( &ibd, &InitData, &m_pIndexBuffer );
	
	return SUCCEEDED( hr );
}
