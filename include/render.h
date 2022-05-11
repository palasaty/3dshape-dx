#pragma once
#include "common.h"

class Render
{
public:
	Render() {}
	virtual ~Render() {}

	virtual bool Init(HWND hwnd) = 0;
	virtual bool Draw() = 0;
	virtual void Close() = 0;
};

class AppRender : public Render
{
public:
	AppRender();

	bool Init(HWND nwnd);
	bool Draw();
	void Close();

private:
	D3D_DRIVER_TYPE m_driverType;
	D3D_FEATURE_LEVEL m_featureLevel;
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pImmediateContext;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
};