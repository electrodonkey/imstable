cmake_minimum_required(VERSION 3.11)

# set the project name
project(imstable VERSION 1.0 LANGUAGES CXX)

# add headers
include_directories(include)
 
# add sources:
file(GLOB SOURCES "source/*.cpp")
 
# add executable 
add_executable(imstable ${SOURCES})

add_subdirectory(test) 

add_subdirectory(documentation)

add_subdirectory(extern)

target_link_libraries(imstable PRIVATE spdlog::spdlog)