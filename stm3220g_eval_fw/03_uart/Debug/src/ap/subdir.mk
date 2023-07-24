################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ap/ap.c 

OBJS += \
./src/ap/ap.o 

C_DEPS += \
./src/ap/ap.d 


# Each subdirectory must supply rules for building sources it contributes
src/ap/%.o src/ap/%.su src/ap/%.cyclo: ../src/ap/%.c src/ap/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F207xx -c -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/USB_DEVICE/App" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/USB_DEVICE/Target" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/ap" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/bsp" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common/inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/hw" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/CMSIS/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/STM32F2xx_HAL_Driver/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-ap

clean-src-2f-ap:
	-$(RM) ./src/ap/ap.cyclo ./src/ap/ap.d ./src/ap/ap.o ./src/ap/ap.su

.PHONY: clean-src-2f-ap

