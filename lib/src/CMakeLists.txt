add_compile_definitions(HZ_BUILD_DLL)

add_library(HazelLib SHARED hzpch.cpp platform/windows/windowswindow.cpp hazel/application.cpp)

add_dependencies(HazelLib glfw)

target_link_libraries(HazelLib glfw opengl32)