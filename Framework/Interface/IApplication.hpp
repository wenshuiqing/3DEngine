#pragma once
#include "Interface.hpp"
#include "IRuntimeModule.hpp"

namespace My{
	Interface IApplication : implements IRuntimeModule
	{
	public:
		virtual int Init() = 0;
		virtual void Destroy() = 0;


		virtual void Update() = 0;

		virtual bool IsQuit() = 0;
		
	};


}
