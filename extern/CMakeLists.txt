cmake_minimum_required(VERSION 3.11)

Include(FetchContent)

FetchContent_Declare(
  Spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.8.2)

FetchContent_MakeAvailable(Spdlog)