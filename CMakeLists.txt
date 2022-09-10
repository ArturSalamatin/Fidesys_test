cmake_minimum_required(VERSION 3.0.0)
project(Fidesys VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(ModelGenerator)
add_subdirectory(StreamOutput)
#add_subdirectory(LagrangeElements)
add_subdirectory(tests)