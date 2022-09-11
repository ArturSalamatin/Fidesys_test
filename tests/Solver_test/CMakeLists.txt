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

add_test(NAME SolverTest2_t COMMAND SolverTest2)

set_tests_properties(SolverTest2_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")




project(SolverTest3)

add_executable(SolverTest3 Solver_test3.cpp)
target_link_libraries(SolverTest3 modelGenerator)

target_compile_features(SolverTest3 PRIVATE cxx_std_17)

add_test(NAME SolverTest3_t COMMAND SolverTest3 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set_tests_properties(SolverTest3_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")




project(SolveTestProblem)
add_executable(SolveTestProblem SolveTestProblem.cpp)
target_link_libraries(SolveTestProblem modelGenerator)
target_compile_features(SolveTestProblem PRIVATE cxx_std_17)




project(SolverTestMeshHomo2)

add_executable(SolverTestMeshHomo2 Solver_testMeshHomo2.cpp)
target_link_libraries(SolverTestMeshHomo2 modelGenerator)

target_compile_features(SolverTestMeshHomo2 PRIVATE cxx_std_17)

add_test(NAME SolverTestMeshHomo2_t COMMAND SolverTestMeshHomo2 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set_tests_properties(SolverTestMeshHomo2_t PROPERTIES
PASS_REGULAR_EXPRESSION "Pass"
FAIL_REGULAR_EXPRESSION "Fail")
