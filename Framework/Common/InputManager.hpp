#pragma once
#include "IRuntimeModule.hpp"

namespace My {

	class  InputManager : implements IRuntimeModule
	{
	public:

		virtual int Init();
		virtual void Update();
		virtual void Destroy();

		void UpArrowKeyDown();
		void UpArrowKeyUp();

		void DownArrowKeyDown();
		void DownArrowKeyUp();

		void LeftArrowKeyDown();
		void LeftArrowKeyUp();

		void RightArrowKeyDown();
		void RightArrowKeyUp();

		void ResetKeyDown();
		void ResetKeyUp();
	private:

	};

	extern InputManager *g_pInputManager;
}

