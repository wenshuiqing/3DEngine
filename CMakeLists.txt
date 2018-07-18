cmake_minimum_required (VERSION 3.1) 
project (3DEngine)

set (CMAKE_C_STANDARD 99)
set (CMAKE_CXX_STANDARD 11)
IF(${UNIX})
    IF(${APPLE})
        set(MYGE_TARGET_PLATFORM "Darwin")
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES Android)
        set(MYGE_TARGET_PLATFORM "Android")
        set(ANDROID 1)
    ELSE(${APPLE})
        set(MYGE_TARGET_PLATFORM "Linux")
    ENDIF(${APPLE})
ELSEIF(${WIN32})
    set(MYGE_TARGET_PLATFORM "Windows")
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES Orbis)
    set(MYGE_TARGET_PLATFORM "Orbis")
    set(ORBIS 1)
ENDIF(${UNIX})
if(NOT MSVC)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-anonymous-struct -Wno-nested-anon-types")
endif(NOT MSVC)
if(ANDROID)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-command-line-argument -Wl,--no-warn-mismatch")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument -Wl,--no-warn-mismatch")
endif(ANDROID)
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -D_DEBUG")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -D_DEBUG")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(TargetArchDetect)

target_architecture(TARGET_ARCH)

if((TARGET_ARCH MATCHES "x86_64" OR TARGET_ARCH MATCHES "ia64") AND NOT OF_32BIT)
        set(ARCH_BIT 64)
else()
        set(ARCH_BIT 32)
endif()

include_directories("${PROJECT_SOURCE_DIR}/Framework/GeomMath/include")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Common")
include_directories("${PROJECT_SOURCE_DIR}/Framework/GeomMath")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Interface")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Parser")
include_directories("${PROJECT_SOURCE_DIR}/RHI")
include_directories("${PROJECT_SOURCE_DIR}/")
include_directories("${PROJECT_SOURCE_DIR}/Platform/${MYGE_TARGET_PLATFORM}")
set(MYGE_EXTERNAL_ROOT ${PROJECT_SOURCE_DIR}/External/${MYGE_TARGET_PLATFORM}/)
include_directories("${MYGE_EXTERNAL_ROOT}include")
include_directories("${MYGE_EXTERNAL_ROOT}include/bullet")
set(MYGE_EXTERNAL_LIBRARY_PATH ${MYGE_EXTERNAL_ROOT}lib/)
find_library(XG_LIBRARY xg PATHS ${MYGE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library(OPENDDL_LIBRARY OpenDDL PATHS ${MYGE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library(OPENGEX_LIBRARY OpenGEX PATHS ${MYGE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library(ZLIB_LIBRARY NAMES z zlib PATHS ${MYGE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library(BULLET_COLLISION_LIBRARY NAMES BulletCollision PATHS ${MYGE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library(BULLET_DYNAMICS_LIBRARY NAMES BulletDynamics PATHS ${MYGE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library(BULLET_LINEARMATH_LIBRARY NAMES LinearMath PATHS ${MYGE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
include(CTest)
include(CheckCXXSourceCompiles)
include(PlatformDependencies)
CHECK_CXX_SOURCE_COMPILES(
"#include <memory>

int main(int argc, char** argv)
{
    std::unique_ptr<int> my_int = std::make_unique<int>();
    *my_int = 0;
    return *my_int;
}
"
 HAVE_MAKE_UNIQUE)
CHECK_CXX_SOURCE_COMPILES(
"#include <algorithm>

int main(int argc, char** argv)
{
    int result = -1;
    result = std::clamp(result, 0, 1);
    return result;
}
"
 HAVE_CLAMP)
configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)
add_subdirectory(Framework)
add_subdirectory(Platform)
add_subdirectory(RHI)
add_subdirectory(Test)



