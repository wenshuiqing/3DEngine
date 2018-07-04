#pragma once
#include "IApplication.hpp"
#include "GraphicsManager.hpp"
#include "MemoryManager.hpp"
#include "AssetLoader.hpp"
#include "SceneManager.hpp"
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
