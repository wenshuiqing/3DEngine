cmake_minimum_required(VERSION 3.5.1)
project(CrossGuid)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

option(XG_TESTS "Build test runner" ON)

include_directories(.)
set(CMAKE_CXX_STANDARD 11)

add_library(xg Guid.cpp)

include(PlatformDependencies)
if (XG_TESTS)
	add_executable(xgtest test/TestMain.cpp test/Test.cpp)
	target_link_libraries(xgtest xg)
	__add_xg_platform_dependencies(xgtest)
endif()


set_target_properties(xg
PROPERTIES PUBLIC_HEADER Guid.hpp
)

install(TARGETS xg
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

