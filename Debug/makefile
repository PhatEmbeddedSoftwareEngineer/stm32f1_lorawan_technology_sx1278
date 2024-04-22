################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := hal_with_stm32f1_sx1278
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
hal_with_stm32f1_sx1278.elf \

MAP_FILES += \
hal_with_stm32f1_sx1278.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
hal_with_stm32f1_sx1278.list \

OBJCOPY_HEX += \
hal_with_stm32f1_sx1278.hex \


# All Target
all: main-build

# Main-build Target
main-build: hal_with_stm32f1_sx1278.elf secondary-outputs

# Tool invocations
hal_with_stm32f1_sx1278.elf hal_with_stm32f1_sx1278.map: $(OBJS) $(USER_OBJS) D:\luu_tru_stm32_thanh_ghi\stm32f4\workspace\MCU1\hal_with_stm32f1_sx1278\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "hal_with_stm32f1_sx1278.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\luu_tru_stm32_thanh_ghi\stm32f4\workspace\MCU1\hal_with_stm32f1_sx1278\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="hal_with_stm32f1_sx1278.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

hal_with_stm32f1_sx1278.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "hal_with_stm32f1_sx1278.list"
	@echo 'Finished building: $@'
	@echo ' '

hal_with_stm32f1_sx1278.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "hal_with_stm32f1_sx1278.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout hal_with_stm32f1_sx1278.elf hal_with_stm32f1_sx1278.hex hal_with_stm32f1_sx1278.list hal_with_stm32f1_sx1278.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
