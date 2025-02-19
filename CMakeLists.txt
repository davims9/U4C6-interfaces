# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================



cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(U4C6-interfaces C CXX ASM)
pico_sdk_init()


# Add executable. Default name is the project name, version 0.1
file(GLOB SOURCES "*.c")
# Inclui todos os arquivos .c da pasta lib
file(GLOB LIB_SOURCES "lib/*.c")
# Combina todos os arquivos em um único executável
add_executable(U4C6-interfaces ${SOURCES} ${LIB_SOURCES})

# Para permitir depuração
pico_enable_stdio_uart(U4C6-interfaces 1)  # Habilita UART
pico_enable_stdio_usb(U4C6-interfaces 1)   # Habilita USB

# gera o arquivo .pio.h
pico_generate_pio_header(U4C6-interfaces ${CMAKE_CURRENT_LIST_DIR}/lib/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/lib)
target_link_libraries(U4C6-interfaces PRIVATE 
    pico_stdlib
    pico_time
    hardware_pio
    hardware_clocks
    hardware_uart
    hardware_i2c
)
pico_add_extra_outputs(U4C6-interfaces) 



