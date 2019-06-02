################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/croutine.c \
/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/MemMang/heap_1.c \
/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/list.c \
/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c \
/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/queue.c \
/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/tasks.c \
/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/timers.c 

OBJS += \
./FreeRTOS/efm32zg/croutine.o \
./FreeRTOS/efm32zg/heap_1.o \
./FreeRTOS/efm32zg/list.o \
./FreeRTOS/efm32zg/port.o \
./FreeRTOS/efm32zg/queue.o \
./FreeRTOS/efm32zg/tasks.o \
./FreeRTOS/efm32zg/timers.o 

C_DEPS += \
./FreeRTOS/efm32zg/croutine.d \
./FreeRTOS/efm32zg/heap_1.d \
./FreeRTOS/efm32zg/list.d \
./FreeRTOS/efm32zg/port_gcc.d \
./FreeRTOS/efm32zg/queue.d \
./FreeRTOS/efm32zg/tasks.d \
./FreeRTOS/efm32zg/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/efm32zg/croutine.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32zg/croutine.d" -MT"FreeRTOS/efm32zg/croutine.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32zg/heap_1.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/MemMang/heap_1.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32zg/heap_1.d" -MT"FreeRTOS/efm32zg/heap_1.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32zg/list.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32zg/list.d" -MT"FreeRTOS/efm32zg/list.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32zg/port.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32zg/port_gcc.d" -MT"FreeRTOS/efm32zg/port_gcc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32zg/queue.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32zg/queue.d" -MT"FreeRTOS/efm32zg/queue.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32zg/tasks.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32zg/tasks.d" -MT"FreeRTOS/efm32zg/tasks.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/efm32zg/timers.o: /opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32ZG/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/EFM32ZG_STK3200/config" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/emlib/inc" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/CMSIS/Include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/bsp" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/kits/common/drivers" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/include" -I"/opt/simplicitystudio3/developer/sdks/efm32/v2/reptile/FreeRTOS/Source/portable/GCC/ARM_CM0" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"FreeRTOS/efm32zg/timers.d" -MT"FreeRTOS/efm32zg/timers.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


