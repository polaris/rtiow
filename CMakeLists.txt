cmake_minimum_required(VERSION 3.26)

project(rtiow VERSION 0.0.1 LANGUAGES CXX)

find_package(Catch2 3 REQUIRED)
find_package(stb)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wformat=2 -Wnull-dereference -Wdouble-promotion -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(COMMON_SOURCES
    vec3.cc
)

add_library(common_objects OBJECT ${COMMON_SOURCES})

add_executable(rtiow main.cc)
set_property(TARGET rtiow PROPERTY CXX_STANDARD 20)
set_property(TARGET rtiow PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(rtiow LINK_PRIVATE stdc++ stb::stb common_objects)

add_executable(tests
               aabb_tests.cc
               thread_pool_tests.cc
               vec3_tests.cc)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)
set_property(TARGET tests PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain common_objects)
