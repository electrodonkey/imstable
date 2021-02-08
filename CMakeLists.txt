cmake_minimum_required(VERSION 3.10)

# set the project name
project(imstable VERSION 1.0 LANGUAGES CXX)

# bring the headers into the project
include_directories(include)
 
# however, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "source/*.cpp")
 
add_executable(imstable ${SOURCES})

add_subdirectory(test) 

add_subdirectory(documentation)