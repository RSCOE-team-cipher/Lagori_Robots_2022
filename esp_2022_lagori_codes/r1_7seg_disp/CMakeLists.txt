cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(r1_7seg C CXX ASM)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

pico_sdk_init()

add_executable(r1_7seg
    r1_7seg.c
)
target_link_libraries(r1_7seg
    pico_stdlib
    hardware_pwm
    hardware_clocks
    pico_multicore
    hardware_uart
    pico_binary_info
    hardware_timer
)

target_include_directories(r1_7seg PUBLIC)

# Configure Pico
pico_enable_stdio_usb(r1_7seg 1)
pico_enable_stdio_uart(r1_7seg 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# Generate UF2
pico_add_extra_outputs(r1_7seg)
