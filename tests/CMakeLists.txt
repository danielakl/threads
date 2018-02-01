include_directories(${CMAKE_SOURCE_DIR})

find_package(Threads REQUIRED)

add_executable(tests tests.cpp ../prime.hpp)
target_link_libraries(tests Threads::Threads)
add_test(tests tests)