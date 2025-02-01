cmake_minimum_required(VERSION 3.20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

project(Asteroids CXX)

add_subdirectory(external)

gem_set_up_workspace("${CMAKE_CURRENT_LIST_DIR}/workspace/"
	PACK_TARGET ASSETS
)

add_subdirectory(asteroids)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT asteroids)
