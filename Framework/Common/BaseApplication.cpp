#include "BaseApplication.hpp"
#include <iostream>

using namespace My;
using namespace std;

bool BaseApplication::m_bQuit = false;

BaseApplication::BaseApplication(GfxConfiguration& cfg)
	:m_Config(cfg)
{
}

// Parse command line, read configuration, initialize all sub modules
int BaseApplication::Init()
{
	int ret = 0;

	cout << m_Config;

	cerr << "Initialize Memory Manager: ";
	if ((ret = g_pMemoryManager->Init()) != 0) {
		cerr << "Failed. err = " << ret;
		return ret;
	}
	cerr << "Success" << endl;

	cerr << "Initialize Asset Loader: ";
	if ((ret = g_pAssetLoader->Init()) != 0) {
		cerr << "Failed. err = " << ret;
		return ret;
	}
	cerr << "Success" << endl;

	cerr << "Initialize Scene Manager: ";
	if ((ret = g_pSceneManager->Init()) != 0) {
		cerr << "Failed. err = " << ret;
		return ret;
	}
	cerr << "Success" << endl;

	cerr << "Initialize Graphics Manager: ";
	if ((ret = g_pGraphicsManager->Init()) != 0) {
		cerr << "Failed. err = " << ret;
		return ret;
	}
	cerr << "Success" << endl;

	cerr << "Initialize Input Manager: ";
	if ((ret = g_pInputManager->Init()) != 0) {
		cerr << "Failed. err = " << ret;
		return ret;
	}
	cerr << "Success" << endl;

	cerr << "Initialize Physics Manager: ";
	if ((ret = g_pPhysicsManager->Init()) != 0) {
		cerr << "Failed. err = " << ret;
		return ret;
	}
	cerr << "Success" << endl;

	return ret;
}

// Finalize all sub modules and clean up all runtime temporary files.
void BaseApplication::Destroy()
{
	g_pInputManager->Destroy();
	g_pGraphicsManager->Destroy();
	g_pPhysicsManager->Destroy();
	g_pSceneManager->Destroy();
	g_pAssetLoader->Destroy();
	g_pMemoryManager->Destroy();
}


// One cycle of the main loop
void BaseApplication::Update()
{
	g_pMemoryManager->Update();
	g_pAssetLoader->Update();
	g_pSceneManager->Update();
	g_pInputManager->Update();
	g_pPhysicsManager->Update();
	g_pGraphicsManager->Update();
}

void BaseApplication::SetCommandLineParameters(int argc, char** argv)
{
	m_nArgC = argc;
	m_ppArgV = argv;
}

bool BaseApplication::IsQuit()
{
	return m_bQuit;
}

int BaseApplication::LoadScene()
{
	int ret;

	string scene_file_name = "Scene/test.ogex";
	if (m_nArgC > 1) {
		scene_file_name = m_ppArgV[1];
	}

	cerr << "Load Scene(" << scene_file_name << "): ";
	if ((ret = g_pSceneManager->LoadScene(scene_file_name.c_str())) != 0) {
		cerr << "Failed. err = " << ret;
		return ret;
	}

	cerr << "Success";

	return 0;
}


