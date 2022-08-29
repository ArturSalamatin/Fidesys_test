cmake_minimum_required(VERSION 3.8)

project(modelGenerator)

set(CPPS ModelGenerator.cpp)

add_library(modelGenerator STATIC ${CPPS})

target_compile_features(modelGenerator PRIVATE cxx_std_17)

# target_link_libraries(patcher lz4 archiver)