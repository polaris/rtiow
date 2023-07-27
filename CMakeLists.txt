cmake_minimum_required(VERSION 3.26)


project(rtiow VERSION 0.0.1 LANGUAGES CXX)


find_package(Catch2 3 REQUIRED)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(COMMON_COMPILE_OPTIONS
    -Wall
    -Wextra
    -Wshadow
    -Wpedantic
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wunused
    -Wno-unused-parameter
    -Wformat=2
    -Werror
)
function(apply_common_compile_options target_name)
    target_compile_options(${target_name} PRIVATE ${COMMON_COMPILE_OPTIONS})
endfunction()


add_library(common_objects OBJECT
    vec3.cc
)


add_executable(rtiow
    main.cc
)
target_link_libraries(rtiow PRIVATE
    stdc++
    common_objects
)
apply_common_compile_options(rtiow)


add_executable(tests
    aabb_tests.cc
    thread_pool_tests.cc
    vec3_tests.cc
)
target_link_libraries(tests PRIVATE
    Catch2::Catch2WithMain
    common_objects
)
apply_common_compile_options(tests)



add_executable(benchmarks
    vec3_benchmarks.cc
)
target_link_libraries(benchmarks PRIVATE
    Catch2::Catch2WithMain
    common_objects
)
apply_common_compile_options(benchmarks)
