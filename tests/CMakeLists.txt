cmake_minimum_required(VERSION 3.8)

project(Tests)

project(TestMethods)
set(CPPS test_methods.cpp)
add_library(TestMethods STATIC ${CPPS})
# target_link_libraries(SolveTestProblem modelGenerator)
target_compile_features(TestMethods PRIVATE cxx_std_17)

add_subdirectory(ModelGenerator_test)
add_subdirectory(LagrangeElement_test)
add_subdirectory(Solver_test)