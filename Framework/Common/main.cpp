#include <stdio.h>
#include <thread>
#include "IApplication.hpp"
#include "GraphicsManager.hpp"
#include "MemoryManager.hpp"
#include "AssetLoader.hpp"
#include "SceneManager.hpp"
using namespace My;

int main(int argc, char** argv) {
	int ret;

	if ((ret = g_pApp->Init()) != 0) {
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pMemoryManager->Init()) != 0) {
		printf("Memory Manager Initialize failed, will exit now.");
		return ret;
	}


	if ((ret = g_pAssetLoader->Init()) != 0) {
		printf("Asset Loader Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pSceneManager->Init()) != 0) {
		printf("Scene Manager Initialize failed, will exit now.");
		return ret;
	}
	g_pSceneManager->LoadScene("Scene/cube.ogex");

	if ((ret = g_pGraphicsManager->Init()) != 0) {
		printf("Graphics Manager Initialize failed, will exit now.");
		return ret;
	}
	while (!g_pApp->IsQuit()) {
		g_pApp->Update();
		g_pMemoryManager->Update();
		g_pAssetLoader->Update();
		g_pSceneManager->Update();
		g_pGraphicsManager->Update();
		std::this_thread::sleep_for(std::chrono::microseconds(10000));
	}

	g_pSceneManager->Destroy();
	g_pAssetLoader->Destroy();
	g_pGraphicsManager->Destroy();
	g_pMemoryManager->Destroy();
	g_pApp->Destroy();

	return 0;

}
