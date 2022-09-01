cmake_minimum_required(VERSION 3.8)

project(KFileParserTest1)

add_executable(kFileParserTest1 KFileParser_test1.cpp)
target_link_libraries(kFileParserTest1 modelGenerator StreamOutput)

target_compile_features(kFileParserTest1 PRIVATE cxx_std_17)

add_test(kFileParserTest1_t kFileParserTest1)

set_tests_properties(kFileParserTest1_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")



project(KFileParserTest2)

add_executable(kFileParserTest2 KFileParser_test2.cpp)
target_link_libraries(kFileParserTest2 modelGenerator StreamOutput)

target_compile_features(kFileParserTest2 PRIVATE cxx_std_17)

add_test(kFileParserTest2_t kFileParserTest2)

set_tests_properties(kFileParserTest2_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")