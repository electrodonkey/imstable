cmake_minimum_required(VERSION 3.11)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.4)

FetchContent_MakeAvailable(Catch2)

add_executable(tests "test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2)