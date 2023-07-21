cmake_minimum_required(VERSION 3.26)

project(rtiow VERSION 0.0.1 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wformat=2 -Wnull-dereference -Wdouble-promotion -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(rtiow main.cc)

set_property(TARGET rtiow PROPERTY CXX_STANDARD 20)

target_link_libraries(rtiow LINK_PRIVATE stdc++)
