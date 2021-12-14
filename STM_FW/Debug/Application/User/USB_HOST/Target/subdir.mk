################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_HOST/Target/usbh_conf.c \
../USB_HOST/Target/usbh_platform.c 

OBJS += \
./Application/User/USB_HOST/Target/usbh_conf.o \
./Application/User/USB_HOST/Target/usbh_platform.o 

C_DEPS += \
./Application/User/USB_HOST/Target/usbh_conf.d \
./Application/User/USB_HOST/Target/usbh_platform.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/USB_HOST/Target/usbh_conf.o: E:/git_repos/DAC/STM_FW/USB_HOST/Target/usbh_conf.c Application/User/USB_HOST/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F730xx -c -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../USB_HOST/App -I../../USB_HOST/Target -I../../Core/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/USB_HOST/Target/usbh_platform.o: E:/git_repos/DAC/STM_FW/USB_HOST/Target/usbh_platform.c Application/User/USB_HOST/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F730xx -c -I../../USB_DEVICE/App -I../../USB_DEVICE/Target -I../../USB_HOST/App -I../../USB_HOST/Target -I../../Core/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-USB_HOST-2f-Target

clean-Application-2f-User-2f-USB_HOST-2f-Target:
	-$(RM) ./Application/User/USB_HOST/Target/usbh_conf.d ./Application/User/USB_HOST/Target/usbh_conf.o ./Application/User/USB_HOST/Target/usbh_platform.d ./Application/User/USB_HOST/Target/usbh_platform.o

.PHONY: clean-Application-2f-User-2f-USB_HOST-2f-Target

