cmake_minimum_required(VERSION 3.10)

# set the project name
project(imstable)

add_subdirectory(source)

# add the executable
add_library (imstable imstable.cxx)