#pragma once
#include "common.h"

class Render
{
public:
	Render();
	virtual ~Render() {}

	bool CreateDevice(HWND hwnd);
	void BeginFrame();
	void EndFrame();
	void Shutdown();

	virtual bool Init(HWND hwnd) = 0;
	virtual bool Draw() = 0;
	virtual void Close() = 0;

protected:
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pImmediateContext;

private:
	D3D_DRIVER_TYPE m_driverType;
	D3D_FEATURE_LEVEL m_featureLevel;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
};

class AppRender : public Render
{
public:
	AppRender();

	bool Init(HWND nwnd);
	bool Draw();
	void Close();

private:
	HRESULT m_compileshaderfromfile(WCHAR* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel, ID3DBlob** ppBlobOut);

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
};