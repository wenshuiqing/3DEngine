#include <iostream>
#include <string>
#include "AssetLoader.hpp"
#include "MemoryManager.hpp"
#include "SceneManager.hpp"

using namespace My;
using namespace std;

namespace My {
    MemoryManager*  g_pMemoryManager = new MemoryManager();
    AssetLoader*    g_pAssetLoader   = new AssetLoader();
    SceneManager*   g_pSceneManager  = new SceneManager();
}

template<typename Key,typename T>
static ostream& operator<<(ostream& out, unordered_map<Key, T> map)
{
    for (auto p : map)
    {
        out << *p.second << endl;
    }

    return out;
}

int main(int , char** )
{
    g_pMemoryManager->Init();
    g_pSceneManager->Init();
    g_pAssetLoader->Init();

    g_pSceneManager->LoadScene("Scene/cube.ogex");
    auto& scene = g_pSceneManager->GetSceneForRendering();

    cout << "Dump of Cameras" << endl;
    cout << "---------------------------" << endl;
    weak_ptr<SceneObjectCamera> pCamera = scene.GetCamera(scene.GetFirstCameraNode()->GetSceneObjectRef());
    while(auto pObj = pCamera.lock())
    {
        cout << *pObj << endl;
        pCamera = scene.GetCamera(scene.GetNextCameraNode()->GetSceneObjectRef());
    }

    cout << "Dump of Lights" << endl;
    cout << "---------------------------" << endl;
    weak_ptr<SceneObjectLight> pLight = scene.GetLight(scene.GetFirstLightNode()->GetSceneObjectRef());
    while(auto pObj = pLight.lock())
    {
        cout << *pObj << endl;
        pLight = scene.GetLight(scene.GetNextLightNode()->GetSceneObjectRef());
    }

    cout << "Dump of Geometries" << endl;
    cout << "---------------------------" << endl;
    weak_ptr<SceneObjectGeometry> pGeometry = scene.GetGeometry(scene.GetFirstGeometryNode()->GetSceneObjectRef());
    while(auto pObj = pGeometry.lock())
    {
        cout << *pObj << endl;
        pGeometry = scene.GetGeometry(scene.GetNextGeometryNode()->GetSceneObjectRef());
    }

    cout << "Dump of Materials" << endl;
    cout << "---------------------------" << endl;
    weak_ptr<SceneObjectMaterial> pMaterial = scene.GetFirstMaterial();
    while(auto pObj = pMaterial.lock())
    {
        cout << *pObj << endl;
        pMaterial = scene.GetNextMaterial();
    }

    g_pSceneManager->Destroy();
    g_pAssetLoader->Destroy();
    g_pMemoryManager->Destroy();

    delete g_pSceneManager;
    delete g_pAssetLoader;
    delete g_pMemoryManager;

    return 0;
}

