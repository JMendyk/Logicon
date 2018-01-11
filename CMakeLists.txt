cmake_minimum_required(VERSION 3.2)

project(LOGICON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")

set(EXECUTABLE_NAME logicon)

add_executable(${EXECUTABLE_NAME} "") # empty "" required for command

include(dependencies/CMakeLists.txt) # additional libraries: glew, imgui etc.

include(include/CMakeLists.txt) # headers in include/ directory

include(src/CMakeLists.txt) # sources

# Copy assets to build directory
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
file(COPY ${ASSETS_DIR} DESTINATION ${CMAKE_BINARY_DIR})

include(CreateDist.cmake) # Redistributable package generation