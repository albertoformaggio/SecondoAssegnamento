cmake_minimum_required(VERSION "3.19.2")

project("ShapeHierarchies" LANGUAGES CXX)

add_library(train train.h train.cpp)
add_library(station station.h station.cpp)
add_library(platform platform.h platform.cpp)
add_library(controller controller.h controller.cpp)

add_executable(main main.cpp)

set_target_properties(train station platform controller PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(main train station platform controller)

set(CMAKE_CXX_FLAGS "-O2")	##optimization flag
