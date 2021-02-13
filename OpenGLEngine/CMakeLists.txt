# CMakeList.txt : CMake project for OpenGLEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add source to this project's executable.
add_executable (
	OpenGLEngine 
	"OpenGLEngine.cpp" 
	"glad.c" 
	"inc/Window.h" 
	"src/Window.cpp"
)

# Add targets 
target_link_libraries (OpenGLEngine glfw)
