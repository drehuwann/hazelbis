cmake_minimum_required(VERSION 3.22)
project(HazelBis VERSION 0.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib/src)
add_subdirectory(sandbox/src)

target_link_libraries(Sandbox PUBLIC HazelLib)

target_include_directories(HazelLib PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/lib/src")

configure_file(HazelBisConfig.h.in HazelBisConfig.h)
