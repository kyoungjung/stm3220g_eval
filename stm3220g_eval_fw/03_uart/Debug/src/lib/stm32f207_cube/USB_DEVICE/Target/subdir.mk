################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/stm32f207_cube/USB_DEVICE/Target/usbd_conf.c 

OBJS += \
./src/lib/stm32f207_cube/USB_DEVICE/Target/usbd_conf.o 

C_DEPS += \
./src/lib/stm32f207_cube/USB_DEVICE/Target/usbd_conf.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/stm32f207_cube/USB_DEVICE/Target/%.o src/lib/stm32f207_cube/USB_DEVICE/Target/%.su src/lib/stm32f207_cube/USB_DEVICE/Target/%.cyclo: ../src/lib/stm32f207_cube/USB_DEVICE/Target/%.c src/lib/stm32f207_cube/USB_DEVICE/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F207xx -c -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/USB_DEVICE/App" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/USB_DEVICE/Target" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/ap" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/bsp" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common/inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/hw" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/CMSIS/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/STM32F2xx_HAL_Driver/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-lib-2f-stm32f207_cube-2f-USB_DEVICE-2f-Target

clean-src-2f-lib-2f-stm32f207_cube-2f-USB_DEVICE-2f-Target:
	-$(RM) ./src/lib/stm32f207_cube/USB_DEVICE/Target/usbd_conf.cyclo ./src/lib/stm32f207_cube/USB_DEVICE/Target/usbd_conf.d ./src/lib/stm32f207_cube/USB_DEVICE/Target/usbd_conf.o ./src/lib/stm32f207_cube/USB_DEVICE/Target/usbd_conf.su

.PHONY: clean-src-2f-lib-2f-stm32f207_cube-2f-USB_DEVICE-2f-Target

