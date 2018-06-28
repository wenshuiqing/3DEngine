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
		virtual void Destroy();
		void LoadOgexScene(const char* scene_file_name);

	protected:
		std::unique_ptr<BaseSceneNode> m_RootNode;
	};
	extern SceneManager* g_pSceneManager;
}