cmake_minimum_required(VERSION "3.10")
project("Rail" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")	##optimization flag

add_library(train train.h RegionalTrain.h HSTrain.h HStrainSuper.h RegionalTrain.cpp HSTrain.cpp HStrainSuper.cpp )
add_library(station station.h station.cpp)
add_library(platform platform.h platform.cpp)
add_library(controller controller.h controller.cpp event.h event.cpp)

add_executable(main main.cpp)

set_target_properties(train station platform controller PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(main train station platform controller)
