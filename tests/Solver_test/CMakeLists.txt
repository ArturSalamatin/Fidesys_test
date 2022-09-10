cmake_minimum_required(VERSION 3.8)

project(SolverTest1)

add_executable(SolverTest1 Solver_test1.cpp)
target_link_libraries(SolverTest1 modelGenerator)

target_compile_features(SolverTest1 PRIVATE cxx_std_17)

add_test(NAME SolverTest1_t COMMAND SolverTest1)

set_tests_properties(SolverTest1_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")

project(SolverTest2)

add_executable(SolverTest2 Solver_test2.cpp)
target_link_libraries(SolverTest2 modelGenerator)

target_compile_features(SolverTest2 PRIVATE cxx_std_17)

add_test(NAME SolverTest2_t COMMAND SolverTest2 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set_tests_properties(SolverTest2_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")