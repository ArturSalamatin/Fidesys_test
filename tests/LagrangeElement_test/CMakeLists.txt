cmake_minimum_required(VERSION 3.8)

project(LagrangeElementTest1)

add_executable(LagrangeElementTest1 LagrangeElement_test1.cpp)
target_link_libraries(LagrangeElementTest1 modelGenerator)

target_compile_features(LagrangeElementTest1 PRIVATE cxx_std_17)

add_test(NAME LagrangeElementTest1_t COMMAND LagrangeElementTest1)

set_tests_properties(LagrangeElementTest1_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")



project(LagrangeElementTest2)

add_executable(LagrangeElementTest2 LagrangeElement_test2.cpp)
target_link_libraries(LagrangeElementTest2 modelGenerator)

target_compile_features(LagrangeElementTest2 PRIVATE cxx_std_17)

add_test(NAME LagrangeElementTest2_t COMMAND LagrangeElementTest1)

set_tests_properties(LagrangeElementTest2_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")



project(LagrangeElementTest3)

add_executable(LagrangeElementTest3 LagrangeElement_test3.cpp)
target_link_libraries(LagrangeElementTest3 modelGenerator)

target_compile_features(LagrangeElementTest3 PRIVATE cxx_std_17)

add_test(NAME LagrangeElementTest3_t COMMAND LagrangeElementTest1)

set_tests_properties(LagrangeElementTest3_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")