#pragma once
#include "Interface.hpp"
#include "IRuntimeModule.hpp"
#include "GfxConfiguration.h"
namespace My{
	Interface IApplication : implements IRuntimeModule
	{
	public:
		virtual int Init() = 0;
		virtual void Destroy() = 0;


		virtual void Update() = 0;

		virtual bool IsQuit() = 0;
		virtual void OnDraw() = 0;
		virtual GfxConfiguration& GetConfiguration() = 0;

		virtual void SetCommandLineParameters(int argc, char** argv) = 0;
		
	};
	extern IApplication*    g_pApp;

}
