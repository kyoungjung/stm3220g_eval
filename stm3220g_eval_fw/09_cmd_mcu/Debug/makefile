################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/lib/stm32f207_cube/USB_DEVICE/Target/subdir.mk
-include src/lib/stm32f207_cube/USB_DEVICE/App/subdir.mk
-include src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include src/lib/stm32f207_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include src/lib/stm32f207_cube/Drivers/STM32F2xx_HAL_Driver/Src/subdir.mk
-include src/hw/deiver/subdir.mk
-include src/hw/subdir.mk
-include src/common/core/subdir.mk
-include src/bsp/startup/subdir.mk
-include src/bsp/subdir.mk
-include src/ap/subdir.mk
-include src/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.managedbuilder.core/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 09_cmd_mcu
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
09_cmd_mcu.elf \

MAP_FILES += \
09_cmd_mcu.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
09_cmd_mcu.list \

OBJCOPY_HEX += \
09_cmd_mcu.hex \

OBJCOPY_BIN += \
09_cmd_mcu.bin \


# All Target
all: main-build

# Main-build Target
main-build: 09_cmd_mcu.elf secondary-outputs

# Tool invocations
09_cmd_mcu.elf 09_cmd_mcu.map: $(OBJS) $(USER_OBJS) D:\git\stm3220g_eval\stm3220g_eval_fw\09_cmd_mcu\src\bsp\ldscript\STM32F207IGHX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "09_cmd_mcu.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\git\stm3220g_eval\stm3220g_eval_fw\09_cmd_mcu\src\bsp\ldscript\STM32F207IGHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="09_cmd_mcu.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

09_cmd_mcu.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "09_cmd_mcu.list"
	@echo 'Finished building: $@'
	@echo ' '

09_cmd_mcu.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "09_cmd_mcu.hex"
	@echo 'Finished building: $@'
	@echo ' '

09_cmd_mcu.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "09_cmd_mcu.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 09_cmd_mcu.bin 09_cmd_mcu.elf 09_cmd_mcu.hex 09_cmd_mcu.list 09_cmd_mcu.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
