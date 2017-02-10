cmake_minimum_required(VERSION 3.0)
project(rtype)

set(CMAKE_GENERATOR CACHE INTERNAL "Visual Studio 14 2015 Win64" FORCE)
set (SFML_ROOT "C:/Program Files/SFML")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/client/cmake_modules" ${CMAKE_MODULE_PATH})

add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)