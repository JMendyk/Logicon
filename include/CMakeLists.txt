# CMake for adding include/ directory to project

set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})

# all headers should be accessed via 'include_subfolder/header.h'
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${INCLUDE_DIR})