#include <iostream>
#include <string>
#include "AssetLoader.hpp"
#include "MemoryManager.hpp"

using namespace std;
using namespace My;

namespace My {
    MemoryManager* g_pMemoryManager = new MemoryManager();
}

int main(int , char** )
{
    g_pMemoryManager->Init();

    AssetLoader asset_loader;
    string shader_pgm = asset_loader.SyncOpenAndReadTextFileToString("Shaders/copy.vs");

    cout << shader_pgm;

    g_pMemoryManager->Destroy();

    delete g_pMemoryManager;

	cin.get();
    return 0;
}

