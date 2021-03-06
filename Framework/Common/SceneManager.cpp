#include "SceneManager.hpp"
#include "AssetLoader.hpp"
#include "OGEX.hpp"

using namespace My;
using namespace std;

SceneManager::~SceneManager()
{
}

int SceneManager::Init()
{
	int result = 0;

	m_pScene = make_shared<Scene>();
	return result;
}

void SceneManager::Destroy()
{
}

void SceneManager::Update()
{
}

int SceneManager::LoadScene(const char* scene_file_name)
{
	// now we only has ogex scene parser, call it directly
	if (LoadOgexScene(scene_file_name)) {
		m_pScene->LoadResource();
		m_bDirtyFlag = true;
		return 0;
	}
	else {
		return -1;
	}
}

void SceneManager::ResetScene()
{
	m_bDirtyFlag = true;
}

bool SceneManager::LoadOgexScene(const char* ogex_scene_file_name)
{
	string ogex_text = g_pAssetLoader->SyncOpenAndReadTextFileToString(ogex_scene_file_name);

	if (ogex_text.empty()) {
		return false;
	}

	OgexParser ogex_parser;
	m_pScene = ogex_parser.Parse(ogex_text);

	if (!m_pScene) {
		return false;
	}

	return true;
}

const Scene& SceneManager::GetSceneForRendering()
{
	return *m_pScene;
}

bool SceneManager::IsSceneChanged()
{
	return m_bDirtyFlag;
}

void SceneManager::NotifySceneIsRenderingQueued()
{
	m_bDirtyFlag = false;
}

