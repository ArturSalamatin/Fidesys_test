cmake_minimum_required(VERSION 3.8)

project(ModelDescriptorTest1)

add_executable(ModelDescriptorTest1 ModelDescriptor_test1.cpp)
target_link_libraries(ModelDescriptorTest1 StreamOutput)

target_compile_features(ModelDescriptorTest1 PRIVATE cxx_std_17)

add_test(ModelDescriptorTest1_t ModelDescriptorTest1)

set_tests_properties(ModelDescriptorTest1_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")



project(ModelDescriptorTest2)

add_executable(ModelDescriptorTest2 ModelDescriptor_test2.cpp)
target_link_libraries(ModelDescriptorTest2 StreamOutput)

target_compile_features(ModelDescriptorTest2 PRIVATE cxx_std_17)

add_test(ModelDescriptorTest2_t ModelDescriptorTest2)

set_tests_properties(ModelDescriptorTest2_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")