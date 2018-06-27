add_executable(AssetLoaderTest AssetLoaderTest.cpp)
target_link_libraries(AssetLoaderTest Common)
add_test(NAME TEST_AssetLoader COMMAND AssetLoaderTest)

add_executable(GeomMathTest GeomMathTest.cpp)
add_test(NAME Test_GeomMath COMMAND GeomMathTest)

add_executable(OgexParserTest OgexParserTest.cpp)
target_link_libraries(OgexParserTest Common ${OPENGEX_LIBRARY} ${OPENDDL_LIBRARY})
add_test(NAME TEST_OgexParser COMMAND OgexParserTest)

add_executable(SceneObjectTest SceneObjectTest.cpp)
target_link_libraries(SceneObjectTest Common ${XG_LIBRARY})
add_test(NAME TEST_SceneObject COMMAND SceneObjectTest)