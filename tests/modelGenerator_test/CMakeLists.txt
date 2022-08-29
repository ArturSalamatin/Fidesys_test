cmake_minimum_required(VERSION 3.8)

project(ModelGeneratorTest)

add_executable(modelGeneratorTest ModelDescriptor_test.cpp)
target_link_libraries(modelGeneratorTest StreamOutput)

target_compile_features(modelGeneratorTest PRIVATE cxx_std_17)

add_test(modelGeneratorTest_t modelGeneratorTest)

set_tests_properties(modelGeneratorTest_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")