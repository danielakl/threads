cmake_minimum_required(VERSION 3.9)
project(threads)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(threads main.cpp prime.hpp)
target_link_libraries(threads Threads::Threads)

enable_testing()
add_subdirectory(tests)