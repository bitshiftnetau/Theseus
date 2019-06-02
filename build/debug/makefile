################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/middleware/subdir.mk
-include src/board/STK3200/subdir.mk
-include src/application/subdir.mk
-include src/HPI/slave/dw1000/ext_interface/spi/subdir.mk
-include src/HPI/slave/dw1000/subdir.mk
-include src/HPI/host/efm32zg222f32/I_O/spi/subdir.mk
-include src/HPI/host/efm32zg222f32/I_O/gpio/subdir.mk
-include src/HPI/host/efm32zg222f32/subdir.mk
-include emlib/subdir.mk
-include CMSIS/efm32zg/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: multidrone_prototype.axf

# Tool invocations
multidrone_prototype.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -T "multidrone_prototype.ld" -Xlinker --gc-sections -Xlinker -Map="multidrone_prototype.map" --specs=nano.specs -o multidrone_prototype.axf "./emlib/em_system.o" "./CMSIS/efm32zg/startup_efm32zg.o" "./CMSIS/efm32zg/system_efm32zg.o" "./src/middleware/mpi_cmu.o" "./src/middleware/mpi_gpio.o" "./src/middleware/mpi_spi.o" "./src/board/STK3200/STK3200_config.o" "./src/application/main.o" "./src/HPI/slave/dw1000/dw1000_device_api.o" "./src/HPI/slave/dw1000/dw1000_mutex.o" "./src/HPI/slave/dw1000/dw1000_param_types.o" "./src/HPI/host/efm32zg222f32/efm32zg_cmu_HPI.o" "./src/HPI/host/efm32zg222f32/efm32zg_gpio_HPI.o" "./src/HPI/host/efm32zg222f32/efm32zg_interrupts_HPI.o" "./src/HPI/host/efm32zg222f32/efm32zg_types_HPI.o" "./src/HPI/host/efm32zg222f32/efm32zg_usart_HPI.o" "./src/middleware/mpi_radio.o" "./src/HPI/slave/dw1000/ext_interface/spi/dw1000_dev_api.o" "./src/HPI/slave/dw1000/ext_interface/spi/dw1000_spi.o" "./src/HPI/host/efm32zg222f32/efm32zg_global_HPI.o" "./src/HPI/host/efm32zg222f32/I_O/spi/efm32zg_spi_HPI.o" "./src/HPI/host/efm32zg222f32/I_O/gpio/efm32zg_gpio_IO_HPI.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: multidrone_prototype.hex'
	arm-none-eabi-objcopy -O ihex "multidrone_prototype.axf" "multidrone_prototype.hex"
	@echo ' '

	@echo 'Building bin file: multidrone_prototype.bin'
	arm-none-eabi-objcopy -O binary "multidrone_prototype.axf" "multidrone_prototype.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "multidrone_prototype.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) multidrone_prototype.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
