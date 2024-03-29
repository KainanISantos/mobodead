CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(mobodead)

set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
set(ALSOFT_CONFIG OFF CACHE BOOL "" FORCE)
set(ALSOFT_AMBDEC_PRESETS OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)

set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glew-cmake)
add_subdirectory(deps/openal-soft)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE src "src/*.cc")

add_executable(${PROJECT_NAME} ${src})
target_include_directories(${PROJECT_NAME} PUBLIC deps/stb)
target_link_libraries(${PROJECT_NAME} glfw libglew_static OpenAL)
