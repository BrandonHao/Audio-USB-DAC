cmake_minimum_required(VERSION 3.18.0)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CWD ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_TOOLCHAIN_FILE ${CWD}/arm-none-eabi-gcc.cmake)

project(DAC_Firmware C)

file(GLOB_RECURSE CMSIS_SOURCE CMAKE_CONFIGURE_DEPENDS
    "${CWD}/cmsis_include/*.h"
    "${CWD}/inc/*.h")

file(GLOB_RECURSE PROJ_SOURCE CMAKE_CONFIGURE_DEPENDS
    "${CWD}/src/*.c")

enable_language(C ASM)
set(CMAKE_C_STANDARD 11)

set(EXECUTABLE ${PROJECT_NAME}.elf)
add_executable(${EXECUTABLE} ${PROJ_SOURCE} ${CMSIS_SOURCE})

target_compile_definitions(${EXECUTABLE} PRIVATE
    -D__SAME70N19__ 
    -DDONT_USE_CMSIS_INIT 
    -DF_CPU=150000000
    -DDEBUG
    COMPONENT_TYPEDEF_STYLE='N')

target_include_directories(${EXECUTABLE} PRIVATE
    inc
    inc/usb
    cmsis_include
    cmsis_include/component
    cmsis_include/instance
    cmsis_include/pio)

target_compile_options(${EXECUTABLE} PRIVATE
    -g3
    -O0
    -fno-diagnostics-show-caret
    -fdata-sections
    -ffunction-sections
    -funsigned-bitfields
    -funsigned-char
    -mthumb 
    -mcpu=cortex-m7 
    -mfloat-abi=hard
    -mfpu=fpv5-d16
    -MD 
    -MP 
    -MT)

target_link_options(${EXECUTABLE} PRIVATE
    -mthumb 
    -mfloat-abi=hard
    -mfpu=fpv5-d16 
    -Wl,--gc-sections 
    -mcpu=cortex-m7
    -Wl,--script=../linker/same70q21.ld)


add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size --format=sysv ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)