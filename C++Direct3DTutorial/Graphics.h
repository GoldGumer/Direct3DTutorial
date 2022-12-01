#pragma once
#include <d3d11.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics();
	void EndFrame();
	void DrawTriangle();
	void ShaderInit();
private:
	ID3D11VertexShader* pVS;
	ID3D11PixelShader* pPS;
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};

