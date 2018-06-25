#pragma once
#include "IRuntimeModule.hpp"

namespace My{
	class GraphicsManager : implements IRuntimeModule{
	public:	
		virtual ~GraphicsManager(){}
		virtual int Init();
		virtual void Destroy();
		virtual void Update();
	};

}
