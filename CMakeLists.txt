cmake_minimum_required(VERSION 3.26)

project(rtiow VERSION 0.0.1 LANGUAGES CXX)

# set(CMAKE_OSX_ARCHITECTURES arm64)

find_package(Catch2 3 REQUIRED)
find_package(stb)

# if(NOT CMAKE_BUILD_TYPE)
#   set(CMAKE_BUILD_TYPE Release)
# endif()

set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wformat=2 -Wnull-dereference -Wdouble-promotion -Wshadow")
# set(CMAKE_CXX_FLAGS_DEBUG "-g")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(rtiow main.cc vec3.cc)
set_property(TARGET rtiow PROPERTY CXX_STANDARD 20)
target_link_libraries(rtiow LINK_PRIVATE stdc++ stb::stb)

add_executable(tests aabb_test.cc vec3_test.cc vec3.cc)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
