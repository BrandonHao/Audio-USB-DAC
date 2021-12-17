cmake_minimum_required(VERSION 3.18.0)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CWD ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_TOOLCHAIN_FILE ${CWD}/arm-none-eabi-gcc.cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(DAC_Firmware C)

file(GLOB_RECURSE CMSIS_SOURCE CMAKE_CONFIGURE_DEPENDS
    "${CWD}/Core/Inc/*.h"
    "${CWD}/Application/*.h"
    "${CWD}/Drivers/STM32F7xx_HAL_Driver/*.h"
    "${CWD}/Drivers/CMSIS/Device/ST/STM32F7xx/*.h"
    "${CWD}/Middlewares/ST/STM32_USB_Device_Library/*.h"
    "${CWD}/USB_DEVICE/*.h")

file(GLOB_RECURSE PROJ_SOURCE CMAKE_CONFIGURE_DEPENDS
    "${CWD}/Core/Src/*.c"
    "${CWD}/Application/*.c"
    "${CWD}/Application/*.s"
    "${CWD}/Drivers/STM32F7xx_HAL_Driver/*.c"
    "${CWD}/Middlewares/*.c"
    "${CWD}/USB_DEVICE/*.c")

set(LINKER_PATH "${CWD}/linker/STM32F730I8KX_FLASH.ld")

enable_language(C ASM)
set(CMAKE_C_STANDARD 11)

set(EXECUTABLE ${PROJECT_NAME}.elf)
add_executable(${EXECUTABLE} ${PROJ_SOURCE} ${CMSIS_SOURCE})

target_compile_definitions(${EXECUTABLE} PRIVATE
    -DDEBUG 
    -DUSE_HAL_DRIVER 
    -DSTM32F730xx)

target_include_directories(${EXECUTABLE} PRIVATE
    USB_DEVICE/App
    USB_DEVICE/Target
    Core/Inc
    Drivers/STM32F7xx_HAL_Driver/Inc
    Drivers/STM32F7xx_HAL_Driver/Inc/Legacy
    Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc
    Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    Drivers/CMSIS/Device/ST/STM32F7xx/Include
    Drivers/CMSIS/Include)

target_compile_options(${EXECUTABLE} PRIVATE
    -mcpu=cortex-m7 
    -std=gnu11 
    -g3
    -O0 
    -ffunction-sections 
    -fdata-sections 
    -Wall 
    -fstack-usage 
    --specs=nano.specs 
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard 
    -mthumb)

target_link_options(${EXECUTABLE} PRIVATE
    -mcpu=cortex-m7 
    -T${LINKER_PATH}
    -Wl,--gc-sections 
    -static 
    --specs=nano.specs 
    -mfpu=fpv5-sp-d16 
    -mfloat-abi=hard 
    -mthumb
    -lc 
    -lm )

set(OUTPUT_FILE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size --format=sysv ${OUTPUT_FILE}.elf)

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${OUTPUT_FILE}.elf ${OUTPUT_FILE}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${OUTPUT_FILE}.elf ${OUTPUT_FILE}.bin)