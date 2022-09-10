cmake_minimum_required(VERSION 3.8)

project(KFileParserTest1)

add_executable(kFileParserTest1 KFileParser_test1.cpp)
target_link_libraries(kFileParserTest1 modelGenerator StreamOutput)

target_compile_features(kFileParserTest1 PRIVATE cxx_std_17)

add_test(NAME kFileParserTest1_t COMMAND kFileParserTest1)

set_tests_properties(kFileParserTest1_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")



project(KFileParserTest2)

add_executable(kFileParserTest2 KFileParser_test2.cpp)
target_link_libraries(kFileParserTest2 modelGenerator StreamOutput)

target_compile_features(kFileParserTest2 PRIVATE cxx_std_17)

add_test(NAME kFileParserTest2_t COMMAND kFileParserTest2 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set_tests_properties(kFileParserTest2_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")


project(KFileParserTest3)

add_executable(kFileParserTest3 KFileParser_test3.cpp)
target_link_libraries(kFileParserTest3 modelGenerator StreamOutput)

target_compile_features(kFileParserTest3 PRIVATE cxx_std_17)

add_test(NAME kFileParserTest3_t COMMAND kFileParserTest3 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set_tests_properties(kFileParserTest3_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")


project(KFileParserTest4)

add_executable(kFileParserTest4 KFileParser_test4.cpp)
target_link_libraries(kFileParserTest4 modelGenerator StreamOutput)

target_compile_features(kFileParserTest4 PRIVATE cxx_std_17)

add_test(NAME kFileParserTest4_t COMMAND kFileParserTest4 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set_tests_properties(kFileParserTest4_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")