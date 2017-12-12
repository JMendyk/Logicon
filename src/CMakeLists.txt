set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

target_sources(${EXECUTABLE_NAME}
    PUBLIC
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/data.h
        ${SRC_DIR}/data.cpp
        ${SRC_DIR}/app.h
        ${SRC_DIR}/app.cpp
        ${SRC_DIR}/engine.h
        ${SRC_DIR}/engine.cpp
        ${SRC_DIR}/circuitParser.h
        ${SRC_DIR}/circuitParser.cpp
        ${SRC_DIR}/gates/circuit.h
        ${SRC_DIR}/gates/circuit.cpp
        ${SRC_DIR}/gates/clock.h
        ${SRC_DIR}/gates/clock.cpp
        ${SRC_DIR}/gates/switch.h
        ${SRC_DIR}/gates/switch.cpp
        ${SRC_DIR}/gates/input.h
        ${SRC_DIR}/gates/input.cpp
        ${SRC_DIR}/gates/and.h
        ${SRC_DIR}/gates/and.cpp
        ${SRC_DIR}/gates/delay.h
        ${SRC_DIR}/gates/delay.cpp
)
