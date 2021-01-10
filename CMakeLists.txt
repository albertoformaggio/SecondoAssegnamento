cmake_minimum_required(VERSION "3.10")
project("Rail" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")	##optimization flag


file(GLOB SRCFILES
	*.cpp
	*.h
	*.txt)

add_executable("${PROJECT_NAME}" ${SRCFILES} "standardPlatform.h" "localStation.h" "mainStation.h" "PlatformRequest.cpp" "controller2.cpp" "parkPlatform.h" "parkPlatform.cpp")