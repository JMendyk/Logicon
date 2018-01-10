set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

# adds files to targer sources
target_sources(${EXECUTABLE_NAME}
    PUBLIC
        ${SRC_DIR}/main.cpp

        ${SRC_DIR}/data.cpp
        ${SRC_DIR}/app.cpp
        ${SRC_DIR}/engine.cpp
        ${SRC_DIR}/fileController.cpp
        ${SRC_DIR}/circuit.cpp
        ${SRC_DIR}/graphics.cpp
        ${SRC_DIR}/logger.cpp

        ${SRC_DIR}/gates/gate.cpp

        ${SRC_DIR}/gates/and.cpp
        ${SRC_DIR}/gates/nand.cpp
        ${SRC_DIR}/gates/nor.cpp
        ${SRC_DIR}/gates/not.cpp
        ${SRC_DIR}/gates/or.cpp
        ${SRC_DIR}/gates/xor.cpp
        ${SRC_DIR}/gates/xnor.cpp

        ${SRC_DIR}/gates/clock.cpp
        ${SRC_DIR}/gates/switch.cpp
        ${SRC_DIR}/gates/input.cpp
        ${SRC_DIR}/gates/delay.cpp

        ${SRC_DIR}/gui/menu_widget.cpp
        ${SRC_DIR}/gui/blocks_widget.cpp
        ${SRC_DIR}/gui/footer_widget.cpp

        ${SRC_DIR}/gui/gHelpers.cpp

        ${SRC_DIR}/exceptions/logiconException.cpp
        ${SRC_DIR}/exceptions/idNotFoundException.cpp
        ${SRC_DIR}/exceptions/wrongPortException.cpp
)
