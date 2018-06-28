#pragma once
// include the basic windows header file
#include <windows.h>
#include <windowsx.h>
#include "BaseApplication.hpp"

namespace My {
	class WindowsApplication : public BaseApplication
	{
	public:
		WindowsApplication(GfxConfiguration& config)
			: BaseApplication(config) {};

		virtual int Init();
		virtual void Destroy();
		// One cycle of the main loop
		virtual void Update();

		HWND GetMainWindow() { return m_hWnd; };

	private:
		// the WindowProc function prototype
		static LRESULT CALLBACK WindowProc(HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam);


	protected:
		HWND m_hWnd;
	};
}

