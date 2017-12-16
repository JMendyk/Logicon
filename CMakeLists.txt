cmake_minimum_required(VERSION 3.2)

project(LOGICON)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_NAME logicon)

add_executable(${EXECUTABLE_NAME} "") # empty "" required for command

include(dependencies/CMakeLists.txt) # additional libraries: glew, imgui etc.

include(include/CMakeLists.txt) # headers in include/ directory

include(src/CMakeLists.txt) # sources

