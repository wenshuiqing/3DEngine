cmake_minimum_required (VERSION 3.1) 

# Windows specific code
set (CMAKE_C_COMPILER               "clang-cl")
set (CMAKE_C_FLAGS_DEBUG            "/Debug /Zi")
set (CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 /Debug")
set (CMAKE_CXX_COMPILER             "clang-cl")
set (CMAKE_CXX_FLAGS_DEBUG          "/Debug /Zi")
set (CMAKE_CXX_FLAGS                "-Wall -Xclang -std=gnu++14")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 /Debug")

set (CMAKE_C_FLAGS                  "-Wall")
set (CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG")
set (CMAKE_C_FLAGS_RELEASE          "-O4 -DNDEBUG")
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")


# ------------------------- End of Generic CMake Variable Logging ------------------

project (3DEngine)
include_directories("${PROJECT_SOURCE_DIR}/Framework/Parser")
include_directories("${PROJECT_SOURCE_DIR}/Framework/GeomMath")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Common")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Interface")
include_directories("${PROJECT_SOURCE_DIR}/RHI")

IF(${UNIX})
    set(MYGE_TARGET_PLATFORM "Linux")
ELSEIF(${WIN32})
    set(MYGE_TARGET_PLATFORM "Windows")
ENDIF(${UNIX})

include_directories("${PROJECT_SOURCE_DIR}/Platform/${MYGE_TARGET_PLATFORM}")
set(MYGE_EXTERNAL_ROOT ${PROJECT_SOURCE_DIR}/External/${MYGE_TARGET_PLATFORM}/)
include_directories("${MYGE_EXTERNAL_ROOT}include")
set(MYGE_EXTERNAL_LIBRARY_PATH ${MYGE_EXTERNAL_ROOT}lib/)
add_subdirectory(Framework)
add_subdirectory(Platform)
add_subdirectory(RHI)
add_subdirectory(Test)
