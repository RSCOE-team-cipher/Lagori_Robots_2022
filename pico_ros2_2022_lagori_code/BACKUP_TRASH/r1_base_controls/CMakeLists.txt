cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(r1_base_controls_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

link_directories(libmicroros)
add_executable(r1_base_controls_pico
    r1_base_controls_pico.c
    pico_uart_transport.c
)
target_link_libraries(r1_base_controls_pico
    pico_stdlib
    microros
    pico_stdlib
    hardware_pwm
    hardware_clocks
    pico_multicore
)

target_include_directories(r1_base_controls_pico PUBLIC
    libmicroros/include
)

SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Configure Pico
pico_enable_stdio_usb(r1_base_controls_pico 1)
pico_enable_stdio_uart(r1_base_controls_pico 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# Generate UF2
pico_add_extra_outputs(r1_base_controls_pico)
