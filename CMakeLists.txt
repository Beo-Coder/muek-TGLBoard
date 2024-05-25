cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(TGL-Board C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()



add_executable(TGL-Board src/main.cpp
        src/display_program.cpp
        src/beo_common.cpp
        src/TextController/tiny_text.cpp
        src/TextController/text_controller.cpp
        src/TextController/static_text.cpp
        src/TextController/scroll_text.cpp
        src/TextController/subcontroller/subcontroller.cpp
        src/TextController/subcontroller/static_subcontroller.cpp
        src/TetrisGame/tetris.cpp
        src/TetrisGame/block.cpp
        src/SnakeAI/snake_ai_animation.cpp
        src/SnakeAI/snake.cpp
        src/SnakeAI/hamiltonian_circle.cpp
        src/SnakeAI/food.cpp
        src/PIOMatrixOutput/pio_matrix_output.cpp
        src/PIOMatrixOutput/color.cpp
        src/Firework/pixel.cpp
        src/Firework/firework_animation.cpp
        src/Firework/firework.cpp
        src/DinoGame/player.cpp
        src/DinoGame/enemy.cpp
        src/DinoGame/dinoGame.cpp
        src/DinoGame/entity.cpp
        src/GameOfLife/game_of_life_animation.cpp
        src/TextController/charsets/charset.cpp
        src/TextController/charsets/letters.cpp
        src/TextController/charsets/tiny_letters.cpp
        src/FlashController/flash_controller.cpp)

target_include_directories(TGL-Board PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

target_link_libraries(TGL-Board pico_stdlib)
target_link_libraries(TGL-Board hardware_pio)
target_link_libraries(TGL-Board hardware_dma)

# printf on USB and on UART
pico_enable_stdio_usb(TGL-Board 1)
pico_enable_stdio_uart(TGL-Board 1)


pico_add_extra_outputs(TGL-Board)

