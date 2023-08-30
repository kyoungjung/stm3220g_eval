################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/deiver/led.c \
../src/hw/deiver/uart.c 

OBJS += \
./src/hw/deiver/led.o \
./src/hw/deiver/uart.o 

C_DEPS += \
./src/hw/deiver/led.d \
./src/hw/deiver/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/deiver/%.o src/hw/deiver/%.su src/hw/deiver/%.cyclo: ../src/hw/deiver/%.c src/hw/deiver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F207xx -c -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/lib/stm32f207_cube/USB_DEVICE/App" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/lib/stm32f207_cube/USB_DEVICE/Target" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/ap" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/bsp" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/common" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/common/inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/hw" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/lib/stm32f207_cube/Drivers/CMSIS/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/lib/stm32f207_cube/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/02_usb_cdc/src/lib/stm32f207_cube/Drivers/STM32F2xx_HAL_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-hw-2f-deiver

clean-src-2f-hw-2f-deiver:
	-$(RM) ./src/hw/deiver/led.cyclo ./src/hw/deiver/led.d ./src/hw/deiver/led.o ./src/hw/deiver/led.su ./src/hw/deiver/uart.cyclo ./src/hw/deiver/uart.d ./src/hw/deiver/uart.o ./src/hw/deiver/uart.su

.PHONY: clean-src-2f-hw-2f-deiver

