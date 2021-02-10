cmake_minimum_required(VERSION 3.16)

set(CMAKE_GENERATOR_PLATFORM Win32)
set(CMAKE_VS_PLATFORM_NAME Win32)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

project(Asteroids CXX)

set(CMAKE_SUPPRESS_REGENERATION ON) # Omit ZERO_CHECK target.

add_subdirectory(external)
add_subdirectory(asteroids)

gem_set_up_workspace("${CMAKE_CURRENT_LIST_DIR}/workspace/")
