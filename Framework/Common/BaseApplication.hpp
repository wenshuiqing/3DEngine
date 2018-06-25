#pragma once
#include "IApplication.hpp"
namespace My{
	class BaseApplication : implements IApplication{
	public:
		BaseApplication(GfxConfiguration& cfg);

		virtual int Init();
		virtual void Destroy();
		virtual void Update();

		virtual bool IsQuit();

		inline GfxConfiguration& GetConfiguration() { return m_Config; }

	protected:
		virtual void OnDraw() {};
	protected:
		static bool m_bQuit;
		GfxConfiguration m_Config;
	private:
		BaseApplication() {};
	
	};


}
