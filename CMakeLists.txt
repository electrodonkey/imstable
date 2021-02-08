cmake_minimum_required(VERSION 3.10)

# set the project name
project(imstable)

# bring the headers into the project
include_directories(include)
 
# however, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "source/*.cpp")
 
add_executable(imstable ${SOURCES})

