cmake_minimum_required(VERSION 3.8)

project(LagrangeElements)

#set(CPPS ModelGenerator.cpp ModelDescriptor.cpp)

#add_library(LagrangeElements STATIC ${CPPS})

target_compile_features(LagrangeElements PRIVATE cxx_std_17)