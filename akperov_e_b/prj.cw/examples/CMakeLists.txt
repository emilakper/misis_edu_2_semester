add_executable(trirastr_test "trirastr_test.cpp")
target_link_libraries(trirastr_test trirastr nlohmann_json::nlohmann_json)

add_executable(trirastr_testVu "trirastr_testVu.cpp")
target_link_libraries(trirastr_testVu trirastr nlohmann_json::nlohmann_json)

add_executable(trirastr_demo "trirastr_demo.cpp")
target_link_libraries(trirastr_demo trirastr nlohmann_json::nlohmann_json)

add_executable(trirastr_demoVu "trirastr_demoVu.cpp")
target_link_libraries(trirastr_demoVu trirastr nlohmann_json::nlohmann_json)