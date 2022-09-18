cmake_minimum_required(VERSION 3.22)
project(HazelBis VERSION 0.9)

IF (WIN32)
  add_compile_definitions(HZ_PLATFORM_WINDOWS)
ELSE()
  # TODO build elsewhere...
ENDIF()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib/src)
add_subdirectory(sandbox/src)

target_link_libraries(Sandbox PUBLIC HazelLib)

target_include_directories(HazelLib PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/lib/src" "${PROJECT_SOURCE_DIR}/lib/src/hazel" "${PROJECT_SOURCE_DIR}/lib/src/design" "${PROJECT_SOURCE_DIR}/lib/src/logger")

configure_file(HazelBisConfig.h.in HazelBisConfig.h)
