#include "Graphics.h"
#include "Vertex.h"
#include <Windows.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);
}

Graphics::~Graphics()
{
	if (pSwap != nullptr)
	{
		pSwap->Release();
	}
	if (pContext != nullptr)
	{
		pContext->Release();
	}
	if (pDevice != nullptr)
	{
		pDevice->Release();
	}
	if (pVS != nullptr)
	{
		pVS->Release();
	}
	if (pPS != nullptr)
	{
		pPS->Release();
	}
}

void Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);
}

void Graphics::DrawTriangle()
{
	//vertices for triangle
	Vertex vertices[3] = { Vertex(0,1,0), Vertex(-1,0,0), Vertex(1,0,0), };
	ID3D11Buffer* pVertexBuffer;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = 0u;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vertices;

	pDevice->CreateBuffer(&bufferDesc, &subData, &pVertexBuffer);

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	pContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);

	ID3DBlob* pBlob;
	
	//Making the shaders
	D3DCompileFromFile(L"Shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &pBlob, 0);

	//setting up vertex shader
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVS);

	//Making the shaders
	D3DCompileFromFile(L"Shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &pBlob, 0);

	//setting up pixel shader
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPS);

	pContext->VSSetShader(pVS, 0, 0);
	pContext->PSSetShader(pPS, 0, 0);

	pContext->Draw( 3u, 0u);
}
