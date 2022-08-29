cmake_minimum_required(VERSION 3.8)

project(StreamOutput)

set(CPPS StreamOutput.cpp)

add_library(StreamOutput STATIC ${CPPS})

target_compile_features(StreamOutput PRIVATE cxx_std_17)