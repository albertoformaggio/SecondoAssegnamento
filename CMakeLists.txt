cmake_minimum_required(VERSION "3.10")
project("Rail" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")	##optimization flag


add_library(train train.h RegionalTrain.h HSTrain.h HSTrainSuper.h RegionalTrain.cpp HSTrain.cpp HSTrainSuper.cpp)
add_library(station station.h mainStation.cpp localStation.cpp)
add_library(platform platform.h standardPlatform.cpp transitPlatform.cpp)
add_library(controller controller.h controller.cpp event.h event.cpp trainStop.cpp)

add_executable(main main.cpp)

set_target_properties(train station platform controller PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(main train station platform controller)
