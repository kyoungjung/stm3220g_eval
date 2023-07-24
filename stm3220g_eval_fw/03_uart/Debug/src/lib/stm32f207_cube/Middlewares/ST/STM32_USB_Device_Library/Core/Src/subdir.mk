################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
../src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
../src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o \
./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o \
./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o 

C_DEPS += \
./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d \
./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d \
./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.o src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.su src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.cyclo: ../src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.c src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F207xx -c -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/USB_DEVICE/App" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/USB_DEVICE/Target" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/ap" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/bsp" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common/inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/hw" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/CMSIS/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/lib/stm32f207_cube/Drivers/STM32F2xx_HAL_Driver/Inc" -I"D:/git/stm3220g_eval/stm3220g_eval_fw/03_uart/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-lib-2f-stm32f207_cube-2f-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src

clean-src-2f-lib-2f-stm32f207_cube-2f-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src:
	-$(RM) ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.cyclo ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.su ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.cyclo ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.su ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.cyclo ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o ./src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.su

.PHONY: clean-src-2f-lib-2f-stm32f207_cube-2f-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src

