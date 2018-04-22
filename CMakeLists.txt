cmake_minimum_required(VERSION 3.10.3)

#project name
project(Msqr)

#add files to compile
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(Msqr ${SOURCES})

#export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Compiler Flags
set(CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++1z -W -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

#Paths
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#Include
include_directories("${PROJECT_SOURCE_DIR}/src")

#FMT
#add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/fmt" EXCLUDE_FROM_ALL)
#target_link_libraries(Msqr fmt::fmt-header-only)
