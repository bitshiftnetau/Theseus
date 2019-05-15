################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Source/system_efm32zg.c 

S_UPPER_SRCS += \
/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Source/GCC/startup_efm32zg.S 

OBJS += \
./CMSIS/efm32zg/startup_efm32zg.o \
./CMSIS/efm32zg/system_efm32zg.o 

C_DEPS += \
./CMSIS/efm32zg/system_efm32zg.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/efm32zg/startup_efm32zg.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Source/GCC/startup_efm32zg.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -c -x assembler-with-cpp -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" '-DEFM32ZG222F32=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/efm32zg/system_efm32zg.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Source/system_efm32zg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"CMSIS/efm32zg/system_efm32zg.d" -MT"CMSIS/efm32zg/system_efm32zg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


