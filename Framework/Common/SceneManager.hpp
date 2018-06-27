#pragma once
#include "geommath.hpp"
#include "IRuntimeModule.hpp"
#include "SceneNode.hpp"

namespace My {

	class SceneManager : implements IRuntimeModule
	{
	public:
		~SceneManager();

		virtual int Init();
		virtual void Update();
		virtual void Destory();
	private:
		SceneEmptyNode m_RootNode;
	};

}