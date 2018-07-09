#include <iostream>
#include <string>
#include "AssetLoader.hpp"
#include "MemoryManager.hpp"
#include "JPEG.hpp"

using namespace std;
using namespace My;

namespace My {
    MemoryManager* g_pMemoryManager = new MemoryManager();
    AssetLoader*   g_pAssetLoader = new AssetLoader();
}

int main(int argc, const char** argv)
{
    g_pMemoryManager->Init();
    g_pAssetLoader->Init();

#ifdef __ORBIS__
    g_pAssetLoader->AddSearchPath("/app0");
#endif

    {
        Buffer buf;
        if (argc >= 2) {
            buf = g_pAssetLoader->SyncOpenAndReadBinary(argv[1]);
        } else {
            buf = g_pAssetLoader->SyncOpenAndReadBinary("Textures/jpeg_decoder_test_6.jpg");
        }

        JfifParser jfif_parser;

        Image image = jfif_parser.Parser(buf);

        cout << image;
    }

    g_pAssetLoader->Destroy();
    g_pMemoryManager->Destroy();

    delete g_pAssetLoader;
    delete g_pMemoryManager;

    return 0;
}
