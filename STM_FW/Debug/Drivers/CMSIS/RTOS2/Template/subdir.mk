################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/RTOS2/Template/cmsis_os1.c 

OBJS += \
./Drivers/CMSIS/RTOS2/Template/cmsis_os1.o 

C_DEPS += \
./Drivers/CMSIS/RTOS2/Template/cmsis_os1.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/RTOS2/Template/%.o: ../Drivers/CMSIS/RTOS2/Template/%.c Drivers/CMSIS/RTOS2/Template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F730xx -c -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../USB_HOST/App -I../../USB_HOST/Target -I../../Core/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-RTOS2-2f-Template

clean-Drivers-2f-CMSIS-2f-RTOS2-2f-Template:
	-$(RM) ./Drivers/CMSIS/RTOS2/Template/cmsis_os1.d ./Drivers/CMSIS/RTOS2/Template/cmsis_os1.o

.PHONY: clean-Drivers-2f-CMSIS-2f-RTOS2-2f-Template

