#include <iostream>
#include <string>
#include "AssetLoader.hpp"
#include "MemoryManager.hpp"

using namespace std;
using namespace My;

namespace My {
    MemoryManager* g_pMemoryManager = new MemoryManager();
    AssetLoader*   g_pAssetLoader = new AssetLoader();
}

int main(int , char** )
{
    g_pMemoryManager->Init();
    g_pAssetLoader->Init();

    g_pAssetLoader->AddSearchPath("/app0");
    string shader_pgm = g_pAssetLoader->SyncOpenAndReadTextFileToString("Shaders/copy.vs");

    cout << shader_pgm;

    g_pAssetLoader->Destroy();
    g_pMemoryManager->Destroy();

    delete g_pAssetLoader;
    delete g_pMemoryManager;

    return 0;
}

