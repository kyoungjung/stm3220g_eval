################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/bsp.c \
../src/bsp/stm32f2xx_hal_msp.c \
../src/bsp/stm32f2xx_it.c \
../src/bsp/syscalls.c \
../src/bsp/sysmem.c \
../src/bsp/system_stm32f2xx.c 

OBJS += \
./src/bsp/bsp.o \
./src/bsp/stm32f2xx_hal_msp.o \
./src/bsp/stm32f2xx_it.o \
./src/bsp/syscalls.o \
./src/bsp/sysmem.o \
./src/bsp/system_stm32f2xx.o 

C_DEPS += \
./src/bsp/bsp.d \
./src/bsp/stm32f2xx_hal_msp.d \
./src/bsp/stm32f2xx_it.d \
./src/bsp/syscalls.d \
./src/bsp/sysmem.d \
./src/bsp/system_stm32f2xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/%.o src/bsp/%.su src/bsp/%.cyclo: ../src/bsp/%.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F207xx -c -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/lib/stm32f207_cube/USB_DEVICE/App" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/lib/stm32f207_cube/USB_DEVICE/Target" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/ap" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/bsp" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/common" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/common/inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/hw" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/lib/stm32f207_cube/Drivers/CMSIS/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/lib/stm32f207_cube/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/lib/stm32f207_cube/Drivers/STM32F2xx_HAL_Driver/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/08_cmd_if/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-bsp

clean-src-2f-bsp:
	-$(RM) ./src/bsp/bsp.cyclo ./src/bsp/bsp.d ./src/bsp/bsp.o ./src/bsp/bsp.su ./src/bsp/stm32f2xx_hal_msp.cyclo ./src/bsp/stm32f2xx_hal_msp.d ./src/bsp/stm32f2xx_hal_msp.o ./src/bsp/stm32f2xx_hal_msp.su ./src/bsp/stm32f2xx_it.cyclo ./src/bsp/stm32f2xx_it.d ./src/bsp/stm32f2xx_it.o ./src/bsp/stm32f2xx_it.su ./src/bsp/syscalls.cyclo ./src/bsp/syscalls.d ./src/bsp/syscalls.o ./src/bsp/syscalls.su ./src/bsp/sysmem.cyclo ./src/bsp/sysmem.d ./src/bsp/sysmem.o ./src/bsp/sysmem.su ./src/bsp/system_stm32f2xx.cyclo ./src/bsp/system_stm32f2xx.d ./src/bsp/system_stm32f2xx.o ./src/bsp/system_stm32f2xx.su

.PHONY: clean-src-2f-bsp

