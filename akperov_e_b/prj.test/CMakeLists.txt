add_executable(rational_test "rational_test.cpp")
target_link_libraries(rational_test rational doctest::doctest)
add_test(NAME rational_test COMMAND rational_test)

add_executable(arrayd_test "arrayd_test.cpp")
target_link_libraries(arrayd_test arrayd doctest::doctest)
add_test(NAME arrayd_test COMMAND arrayd_test)


add_executable(matrixs_test "matrixs_test.cpp")
target_link_libraries(matrixs_test matrixs doctest::doctest)
add_test(NAME matrixs_test COMMAND matrixs_test)


add_executable(arrayt_test "arrayt_test.cpp")
target_link_libraries(arrayt_test arrayt doctest::doctest)
add_test(NAME arrayt_test COMMAND arrayt_test)

#add_executable(geo2d_test "geo2d_test.cpp")
#target_link_libraries(geo2d_test geo2d doctest::doctest)
#add_test(NAME geo2d_test COMMAND geo2d_test)

#add_executable(trirastr_test1 "trirastr_test1.cpp")
#target_link_libraries(trirastr_test1 trirastr opencv_core nlohmann_json::nlohmann_json)

#add_executable(trirastr_test2 "trirastr_test2.cpp")
#target_link_libraries(trirastr_test2 trirastr opencv_core nlohmann_json::nlohmann_json)

#add_executable(trirastr_demo1 "trirastr_demo1.cpp")
#target_link_libraries(trirastr_demo1 trirastr opencv_core nlohmann_json::nlohmann_json)

#add_executable(trirastr_demo2 "trirastr_demo2.cpp")
#target_link_libraries(trirastr_demo2 trirastr opencv_core nlohmann_json::nlohmann_json)