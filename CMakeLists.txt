cmake_minimum_required(VERSION 3.6)
project(IF2110_Mobita VERSION 0.0.1)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.h src/*.c)
list(FILTER sources EXCLUDE REGEX "_driver.c")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(main ${sources})
