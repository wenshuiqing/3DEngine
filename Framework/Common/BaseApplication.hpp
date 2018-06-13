#pragma once
#include "IApplication.hpp"

namespace My{
	class BaseApplication : implements IApplication{
	public:
		virtual int Init();
		virtual void Destroy();
		virtual void Update();

		virtual bool IsQuit();


	protected:
		bool m_bQuit;
	
	
	};


}
