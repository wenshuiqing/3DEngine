add_library(Common
Image.cpp
AssetLoader.cpp
Allocator.cpp
BaseApplication.cpp
GraphicsManager.cpp
SceneManager.cpp
MemoryManager.cpp
main.cpp
)
find_library(XG_LIBRARY xg PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
find_library(OPENDDL_LIBRARY OpenDDL PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
find_library(OPENGEX_LIBRARY OpenGEX PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
