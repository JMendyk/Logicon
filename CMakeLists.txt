cmake_minimum_required(VERSION 3.2)

project(LOGICON)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_NAME logicon)
add_executable(${EXECUTABLE_NAME} "")

include(dependencies/CMakeLists.txt)

include(src/CMakeLists.txt)
