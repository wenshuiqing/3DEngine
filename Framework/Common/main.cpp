#include <iostream>
#include "IApplication.hpp"

using namespace My;

namespace My {
	extern IApplication* g_pApp;
}

int main(int argc, char** argv) {
	int ret = 0;

	if ((ret = g_pApp->Init()) != 0) {
		std::cout << "init is fail" << std::endl;
		return ret;
	}

	while (!g_pApp->IsQuit()) {
		g_pApp->Update();
	}

	g_pApp->Destroy();

	return 0;

}
