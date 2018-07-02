#生成静态库
add_library(Common
Image.cpp
AssetLoader.cpp
Allocator.cpp
BaseApplication.cpp
GraphicsManager.cpp
SceneManager.cpp
MemoryManager.cpp
SceneParser.cpp
SceneObject.cpp
main.cpp
)

if(WIN32)
    add_definitions(-DGUID_WINDOWS)
elseif(APPLE)
    add_definitions(-DGUID_CFUUID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
elseif(ANDROID)
    target_compile_definitions(Common PRIVATE GUID_ANDROID)
else()
    include_directories(${LIBUUID_INCLUDE_DIR})
    add_definitions(-DGUID_LIBUUID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()