// include the basic windows header file
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <d2d1.h>

ID2D1Factory *pDirect2dFactory = nullptr;
ID2D1HwndRenderTarget *pRenderTarget = nullptr;
ID2D1SolidColorBrush *pLightSlateGrayBrush = nullptr;
ID2D1SolidColorBrush *pCornflowerBlueBrush = nullptr;


template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


HRESULT CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pDirect2dFactory);

	return hr;
}

HRESULT CreateDeviceResources(HWND hWnd)
{
	HRESULT hr = S_OK;

	if (!pRenderTarget)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		// Create a Direct2D render target.
		hr = pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&pRenderTarget
		);


		if (SUCCEEDED(hr))
		{
			// Create a gray brush.
			hr = pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
				&pLightSlateGrayBrush
			);
		}
		if (SUCCEEDED(hr))
		{
			// Create a blue brush.
			hr = pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
				&pCornflowerBlueBrush
			);
		}
	}

	return hr;
}

void DiscardDeviceResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pLightSlateGrayBrush);
	SafeRelease(&pCornflowerBlueBrush);
}


HRESULT Render(HWND hWnd) {
	HRESULT hr = S_OK;
	hr = CreateDeviceResources(hWnd);

	if (SUCCEEDED(hr))
	{
		pRenderTarget->BeginDraw();

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		D2D1_SIZE_F rtSize = pRenderTarget->GetSize();

		// Draw a grid background.
		int width = static_cast<int>(rtSize.width);
		int height = static_cast<int>(rtSize.height);

		for (int x = 0; x < width; x += 10)
		{
			pRenderTarget->DrawLine(
				D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
				D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
				pLightSlateGrayBrush,
				0.5f
			);
		}

		for (int y = 0; y < height; y += 10)
		{
			pRenderTarget->DrawLine(
				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
				pLightSlateGrayBrush,
				0.5f
			);
		}

		// Draw two rectangles.
		D2D1_RECT_F rectangle1 = D2D1::RectF(
			rtSize.width / 2 - 50.0f,
			rtSize.height / 2 - 50.0f,
			rtSize.width / 2 + 50.0f,
			rtSize.height / 2 + 50.0f
		);

		D2D1_RECT_F rectangle2 = D2D1::RectF(
			rtSize.width / 2 - 100.0f,
			rtSize.height / 2 - 100.0f,
			rtSize.width / 2 + 100.0f,
			rtSize.height / 2 + 100.0f
		);

		// Draw a filled rectangle.
		pRenderTarget->FillRectangle(&rectangle1, pLightSlateGrayBrush);

		// Draw the outline of a rectangle.
		pRenderTarget->DrawRectangle(&rectangle2, pCornflowerBlueBrush);


		hr = pRenderTarget->EndDraw();

		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}
		return hr;
	}
}

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{
	// the handle for the window, filled by a function
	HWND hWnd;
	if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) return -1;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = _T("WindowClass1");

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(0,
		_T("WindowClass1"),    // name of the window class
		_T("Hello, Engine!"),   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		800,    // width of the window
		600,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg;
	// wait for the next message in the queue, store the result in 'msg'
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// translate keystroke messages into the right format
		TranslateMessage(&msg);

		// send the message to the WindowProc function
		DispatchMessage(&msg);
	}
	CoUninitialize();
	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int result = 0;
	bool wasHandled = false;
	// sort through and find what code to run for the message given
	switch (message)
	{
	case WM_CREATE:

		if (FAILED(CreateDeviceIndependentResources()))
		{
			result = -1;
			return result;
		}
		wasHandled = true;
		result = 0;
		break;
	case WM_PAINT:

		Render(hWnd);

		break;
		// this message is read when the window is closed

	case WM_SIZE:
		if (pRenderTarget != nullptr)
		{
			RECT rc;
			GetClientRect(hWnd, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

			pRenderTarget->Resize(size);
		}
		wasHandled = true;
		break;
	case WM_DESTROY:
		// close the application entirely
		DiscardDeviceResources();
		PostQuitMessage(0);
		return 0;
		break;

	case WM_DISPLAYCHANGE:
		InvalidateRect(hWnd, nullptr, false);
		wasHandled = true;
		break;
	}

	// Handle any messages the switch statement didn't
	if (!wasHandled) { result = DefWindowProc(hWnd, message, wParam, lParam); }
	return result;
}
