#pragma once


#include <dxgi1_4.h>
#include<d3d12.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include "d3dx12.h"
#include "DXSampleHelper.h"
#include "Win32Application.h"

class DXSample
{
public:
	DXSample(UINT width, UINT height, std::wstring name);
	virtual ~DXSample();

	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnDestroy() = 0;

	UINT GetWidth() const { return m_width; }
	UINT GetHeight() const { return m_height; }
	const WCHAR* GetTitle() const { return m_title.c_str(); }

	void ParseCommandLineArgs(_In_reads_(argc) WCHAR* argv[], int argc);

protected:
	std::wstring GetAssetFullPath(LPCWSTR assetName);
	void GetHardwareAdapter(_In_ IDXGIFactory2* pFactory, _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter);
	void SetCustomWindowText(LPCWSTR text);

	UINT m_width;
	UINT m_height;
	float m_aspectRatio;

	bool m_useWarpDevice;

private:
	std::wstring m_assetsPath;
	std::wstring m_title;
};

