#pragma once

#include "Interface.hpp"

namespace My{
	Interface IRuntimeModule{
	public:
		virtual ~IRuntimeModule(){};

		virtual int Init() = 0;
		virtual void Destroy() = 0;

		virtual void Update() = 0;
	
	};
	


}
