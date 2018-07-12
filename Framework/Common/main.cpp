#include <cstdio>
#include <chrono>
#include <thread>
#include "BaseApplication.hpp"

using namespace My;
using namespace std;

int main(int argc, char** argv) {
	int ret;

	g_pApp->SetCommandLineParameters(argc, argv);

	if ((ret = g_pApp->Init()) != 0) {
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pApp->LoadScene()) != 0) {
		printf("Load Scene failed, will exit now.");
		return ret;
	}

	while (!g_pApp->IsQuit()) {
		g_pApp->Update();

	}

	g_pApp->Destroy();

	return 0;

}
