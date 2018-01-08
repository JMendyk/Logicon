set(DEPS_DIR ${CMAKE_CURRENT_LIST_DIR})

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})

##### GL3W #####
set(GL3W_DIR ${DEPS_DIR}/gl3w)

add_subdirectory(${GL3W_DIR})
include_directories(${GL3W_DIR}/include)
target_sources(${EXECUTABLE_NAME}
    PUBLIC
        ${GL3W_DIR}/src/gl3w.c
)

##### GLFW #####
set(GLFW_DIR ${DEPS_DIR}/glfw)

# Disable generation of docs, tests and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_DIR})
target_link_libraries(${EXECUTABLE_NAME} glfw)

##### ImGUI #####
set(IMGUI_DIR ${DEPS_DIR}/imgui)

# Tells ImGUI to include user addons, such as imguifilesystem
target_compile_definitions(${EXECUTABLE_NAME} PUBLIC IMGUI_INCLUDE_IMGUI_USER_H IMGUI_INCLUDE_IMGUI_USER_INL)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${IMGUI_DIR})
target_sources(${EXECUTABLE_NAME}
    PUBLIC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        # Uncomment if you want to use demo functionalities
        ${IMGUI_DIR}/imgui_demo.cpp
)

##### imgui_impl_glfw_gl3 #####
set(IMGUI_IMPL_GLFW_GL3_DIR ${DEPS_DIR}/imgui_impl_glfw_gl3)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${IMGUI_IMPL_GLFW_GL3_DIR})
target_sources(${EXECUTABLE_NAME} 
    PUBLIC
        ${IMGUI_IMPL_GLFW_GL3_DIR}/imgui_impl_glfw_gl3.cpp
)

###### json #####
set(JSON_DIR ${DEPS_DIR}/json)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${JSON_DIR})

###### stb_image #####
set(STB_IMAGE_DIR ${DEPS_DIR}/stb_image)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${STB_IMAGE_DIR})
