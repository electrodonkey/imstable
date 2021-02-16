cmake_minimum_required(VERSION 3.11)

# set the project name
project(imstable VERSION 1.0 LANGUAGES CXX)

# add headers
include_directories(include)
 
# add sources
file(GLOB SOURCES "source/*.cpp")
 
# create shared lib
add_library (imstable ${SOURCES})

# create demo executable
add_executable(imstable_demo "demo/imstable.cpp")

# add tests
add_subdirectory(test) 

# add documentation
add_subdirectory(documentation)

# add external dependencies
add_subdirectory(extern)

# link libraries
target_link_libraries(imstable PUBLIC spdlog::spdlog)
target_link_libraries(imstable_demo PUBLIC imstable)