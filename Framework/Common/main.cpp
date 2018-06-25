#include <stdio.h>
#include "IApplication.hpp"
#include "GraphicsManager.hpp"
#include "MemoryManager.hpp"
using namespace My;

namespace My {
	extern IApplication*    g_pApp;
	extern MemoryManager*   g_pMemoryManager;
	extern GraphicsManager* g_pGraphicsManager;
}

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

	if ((ret = g_pGraphicsManager->Init()) != 0) {
		printf("Graphics Manager Initialize failed, will exit now.");
		return ret;
	}

	while (!g_pApp->IsQuit()) {
		g_pApp->Update();
		g_pMemoryManager->Update();
		g_pGraphicsManager->Update();
	}

	g_pGraphicsManager->Destroy();
	g_pMemoryManager->Destroy();
	g_pApp->Destroy();

	return 0;

}
