##################################
#																 #
# Makefile - entertainment_IPS   #
#																 #
# 	System - efm32zg222f32       #
#				OS - FreeRTOS            #
#																 #
#		Author - Aidan Millar Powell #
#		 Alias - MedicineMan25       #
#																 #
##################################

#################################
# 				CONSTANTS
#################################

ARM_GCC_VERS=8.3.0
GCC_ARM=/usr/arm-none-eabi
GCC_LIB_ARM=/usr/lib/gcc/arm-none-eabi/$(ARM_GCC_VERS)

SOURCE_DIR=../../src
SDK_DIR=/usr/include/sdks/gecko_sdk
CMSIS_DIR=$(SDK_DIR)/platform/CMSIS
DEVICE_DIR=$(SDK_DIR)/platform/Device/SiliconLabs/EFM32ZG
FREERTOS_DIR=$(SDK_DIR)/util/third_party/freertos
DEP_LIST_OUT=./CMSIS/efm32zg/system_efm32zg.d
EM_LIB=$(SDK_DIR)/platform/emlib/inc
STK3200_DIR=$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200
BSP_DIR=$(SDK_DIR)/hardware/kit/common/bsp

PROJECT_NAME=spongecake
TARGET=$(PROJECT_NAME).axf 


#################################
# 			    INCLUDE	
#################################

GCC_INCLUDE= \
-I$(GCC_ARM)/include \
-I$(GCC_LIB_ARM)/include \
-I$(GCC_LIB_ARM)/include-fixed

CMSIS_INCLUDE= \
-I$(CMSIS_DIR)/Include

DEVICE_INCLUDE= \
-I$(DEVICE_DIR)/Include

EM_INCLUDE= \
-I$(EM_LIB)

BSP_INCLUDE = \
-I$(BSP_DIR)

STK3200_INCLUDE= \
-I$(STK3200_DIR)/config

PROJECT_INCLUDE= \
-I$(SOURCE_DIR)/HAL/host/efm32zg222f32 \
-I$(SOURCE_DIR)/HAL/slave/dw1000 \
-I$(SOURCE_DIR)/HAL/slave/venus638 \
-I$(SOURCE_DIR)/application/app_fns \
-I$(SOURCE_DIR)/application/configs \
-I$(SOURCE_DIR)/port_adaptors \
-I$(SOURCE_DIR)/middleware \
-I$(SOURCE_DIR)/board/STK3200 \

#FREERTOS_INCLUDE= \
#-I$(FREERTOS_DIR)/include

INCLUDE= \
$(GCC_INCLUDE) \
$(CMSIS_INCLUDE) \
$(DEVICE_INCLUDE) \
$(EM_INCLUDE) \
$(BSP_INCLUDE) \
$(STK3200_INCLUDE) \
$(PROJECT_INCLUDE) 
#$(FREERTOS_INCLUDE)

#################################
# 			    SOURCES	
#################################

#FREERTOS_SOURCES= \
$(FREERTOS_DIR)/Source/*.c

PROJECT_SOURCES= \
$(wildcard $(SOURCE_DIR)/HAL/host/efm32zg222f32/*.c) \
$(wildcard $(SOURCE_DIR)/HAL/slave/dw1000/*.c) \
$(wildcard $(SOURCE_DIR)/HAL/slave/venus638/*.c) \
$(wildcard $(SOURCE_DIR)/middleware/*.c) \
$(wildcard $(SOURCE_DIR)/board/STK3200/*.c) \
$(wildcard $(SOURCE_DIR)/application/app_fns/*.c) \
$(wildcard $(SOURCE_DIR)/application/configs/*.c) \
$(wildcard $(SOURCE_DIR)/application/*.c) \
$(wildcard $(SOURCE_DIR)/port_adaptors/*.c)

SOURCES= \
$(PROJECT_SOURCES)


#################################
# 			    OBJECTS	
#################################

OBJECTS= \
$(SOURCES:.c=.o)



#################################
# 			  DIRECTORIES 	
#################################

SRC_DIR = \
$(PROJECT_SOURCES)


#################################
# 		    BUILD FLAGS 				  	
#################################

CC=arm-none-eabi-gcc
LD=$(CC)

#EFM32ZG_FLAG='-DEFM32ZG222F32=1'
#VENUS_FLAG='-DVENUS638=1'
#BUILD_CONFIG_1.1.1.1.1='-DEL_BOM00001_HAL0001_MW0001_A0001_R0001=1'

CFLAGS= -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' '-DDEFAULT_HFRCO_14MHZ' '-DVENUS638=1' '-DDW1000=1' $(INCLUDE) -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections 

LDFLAGS= \
 -L$(GCC_LIB_ARM)/thumb/v6-m/nofp \
 -L$(GCC_ARM)/lib/thumb/v6-m/nofp \
 -L$(CMSIS_DIR)/Lib/GCC \
 -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -T "efm32zg.ld" -Xlinker --gc-sections -Xlinker -Map="efm32zg.map" --specs=nano.specs -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group

#CPPFLAGS=$(INCLUDE)

BUILD_DIR=.

#################################
# 		   BUILD TARGETS 				  
#################################

#assembly: $(SRC_DIR)
#	$(CC) $(CPPFLAGS) $(CFLAGS) -S $^ 

all: $(TARGET)
	arm-none-eabi-objcopy -O ihex "$(PROJECT_NAME).axf" "$(PROJECT_NAME).hex"
	arm-none-eabi-objcopy -O binary "$(PROJECT_NAME).axf" "$(PROJECT_NAME).bin"
	arm-none-eabi-size "$(PROJECT_NAME).axf"

$(TARGET): startup_efm32zg.o system_efm32zg.o $(OBJECTS)
	$(LD) -o $@ $(wildcard $(BUILD_DIR)/*.o) $(LDFLAGS)

$(OBJECTS): $(SRC_DIR)
	$(CC) $(CFLAGS) $^  

startup_efm32zg.o: $(DEVICE_DIR)/Source/GCC/startup_efm32zg.S
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -c -x assembler-with-cpp \
	 	-I"$(SDK_DIR)/platform/Device/SiliconLabs/EFM32ZG/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
		-I"$(EM_LIB)" \
	 	-I"$(SDK_DIR)/platform/CMSIS/Include" \
		-I"$(SDK_DIR)/hardware/kit/common/bsp" \
		-I"$(SDK_DIR)/hardware/kit/common/drivers" \
	 	-I"$(FREERTOS_DIR)/Source/include" \
	 	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
	 	'-DEFM32ZG222F32=1' -o "$@" "$<" 
	@echo 'Finished building: $<' 
	@echo ' '

system_efm32zg.o: $(DEVICE_DIR)/Source/system_efm32zg.c
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' \
	 	-I"$(SDK_DIR)/platform/Device/SiliconLabs/EFM32ZG/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
	 	-I"$(EM_LIB)" \
	 	-I"$(SDK_DIR)/platform/CMSIS/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/common/bsp" \
	 	-I"$(SDK_DIR)/hardware/kit/common/drivers" \
	 	-I"$(FREERTOS_DIR)/Source/include" \
	 	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
	 	-O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP \
	 	-MF"$(DEP_LIST_OUT)" \
	 	-MT"system_efm32zg.o"  -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo ' '


#clean:
#	rm $(TARGET) $(OBJECTS)

clean:
	rm $(TARGET) $(BUILD_DIR)/*.o $(PROJECT_NAME).hex $(PROJECT_NAME).bin CMSIS/efm32zg/system_efm32zg.d
.PHONY: all clean assembly


#
# FreeRTOS 
#

# Add inputs and outputs from these tool invocations to the build variables 
#C_SRCS += \
$(FREERTOS_DIR)/Source/croutine.c \
$(FREERTOS_DIR)/Source/portable/MemMang/heap_1.c \
$(FREERTOS_DIR)/Source/list.c \
$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0/port.c \
$(FREERTOS_DIR)/Source/queue.c \
$(FREERTOS_DIR)/Source/tasks.c \
$(FREERTOS_DIR)/Source/timers.c 

#OBJS += \
$(FREERTOS_DIR)/Source/croutine.o \
$(FREERTOS_DIR)/Source/heap_1.o \
$(FREERTOS_DIR)/Source/list.o \
$(FREERTOS_DIR)/Source/port.o \
$(FREERTOS_DIR)/Source/queue.o \
$(FREERTOS_DIR)/Source/tasks.o \
$(FREERTOS_DIR)/Source/timers.o 

#C_DEPS += \
$(FREERTOS_DIR)/Source/croutine.d \
$(FREERTOS_DIR)/Source/heap_1.d \
$(FREERTOS_DIR)/Source/list.d \
$(FREERTOS_DIR)/Source/port_gcc.d \
$(FREERTOS_DIR)/Source/queue.d \
$(FREERTOS_DIR)/Source/tasks.d \
$(FREERTOS_DIR)/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
#routine.o: $(FREERTOS_DIR)/Source/croutine.c
#	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' \
	 	-I"$(DEVICE_DIR)/Device/SiliconLabs/EFM32ZG/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
	 	-I"$(CMSIS_DIR)/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/common/bsp" \
		 	-I"$(SDK_DIR)/hardware/kit/common/drivers" \
		 	-I"$(FREERTOS_DIR)/Source/include" \
	   	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
 	  	-O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP \
		 	-MF"$(FREERTOS_DIR)/croutine.d" \
	  	-MT"$(FREERTOS_DIR)/croutine.o" -o "$@" "$<"
#	@echo 'Finished building: $<'
#	@echo ' '

#heap_1.o: $(FREERTOS_DIR)/Source/portable/MemMang/heap_1.c
#	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' \
	 	-I"$(DEVICE_DIR)/Device/SiliconLabs/EFM32ZG/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
	 	-I"$(CMSIS_DIR)/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/common/bsp" \
	 	-I"$(SDK_DIR)/hardware/kit/common/drivers" \
	 	-I"$(FREERTOS_DIR)/Source/include" \
	 	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
	 	-O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP \
	 	-MF"$(FREERTOS_DIR)/heap_1.d" \
	 	-MT"$(FREERTOS_DIR)/heap_1.o" -o "$@" "$<"
#	@echo 'Finished building: $<'
#	@echo ' '

#list.o: $(FREERTOS_DIR)/Source/list.c
#	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' \
	 	-I"$(DEVICE_DIR)/Device/SiliconLabs/EFM32ZG/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
	 	-I"$(CMSIS_DIR)/Include" \
	  -I"$(SDK_DIR)/hardware/kit/common/bsp" \
  	-I"$(SDK_DIR)/hardware/kit/common/drivers" \
	 	-I"$(FREERTOS_DIR)/Source/include" \
	 	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
	 	-O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP \
	 	-MF"$(FREERTOS_DIR)/list.d" \
	 	-MT"$(FREERTOS_DIR)/list.o" -o "$@" "$<"
#	@echo 'Finished building: $<'
#	@echo ' '

#port.o: $(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0/port.c
#	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' \
	 	-I"$(DEVICE_DIR)/Device/SiliconLabs/EFM32ZG/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
	 	-I"$(CMSIS_DIR)/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/common/bsp" \
	 	-I"$(SDK_DIR)/hardware/kit/common/drivers" \
	 	-I"$(FREERTOS_DIR)/Source/include" \
	 	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
	 	-O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP \
	 	-MF"$(FREERTOS_DIR)/port_gcc.d" \
	 	-MT"$(FREERTOS_DIR)/port_gcc.o" -o "$@" "$<"
#	@echo 'Finished building: $<'
#	@echo ' '

#queue.o: $(FREERTOS_DIR)/Source/queue.c
#	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' \
	 	-I"$(DEVICE_DIR)/Device/SiliconLabs/EFM32ZG/Include" \
		-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
	 	-I"$(CMSIS_DIR)/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/common/bsp" \
	 	-I"$(SDK_DIR)/hardware/kit/common/drivers" \
	 	-I"$(FREERTOS_DIR)/Source/include" \
	 	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
	 	-O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP \
	 	-MF"$(FREERTOS_DIR)/queue.d" \
	 	-MT"$(FREERTOS_DIR)/queue.o" -o "$@" "$<"
#	@echo 'Finished building: $<'
#	@echo ' '

#tasks.o: $(FREERTOS_DIR)/Source/tasks.c
#	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' \
	 	-I"$(DEVICE_DIR)/Device/SiliconLabs/EFM32ZG/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
	 	-I"$(CMSIS_DIR)/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/common/bsp" \
	 	-I"$(SDK_DIR)/hardware/kit/common/drivers" \
	 	-I"$(FREERTOS_DIR)/Source/include" \
	 	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
	 	-O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP \
	 	-MF"$(FREERTOS_DIR)/tasks.d" \
	 	-MT"$(FREERTOS_DIR)/tasks.o" -o "$@" "$<"
#	@echo 'Finished building: $<'
#	@echo ' '

#timers.o: $(FREERTOS_DIR)/Source/timers.c
#	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb '-DEFM32ZG222F32=1' \
	 	-I"$(DEVICE_DIR)/Device/SiliconLabs/EFM32ZG/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/EFM32ZG_STK3200/config" \
	 	-I"$(CMSIS_DIR)/Include" \
	 	-I"$(SDK_DIR)/hardware/kit/common/bsp" \
	 	-I"$(SDK_DIR)/hardware/kit/common/drivers" \
	 	-I"$(FREERTOS_DIR)/Source/include" \
	 	-I"$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM0" \
	 	-O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP \
	 	-MF"$(FREERTOS_DIR)/timers.d" \
	 	-MT"$(FREERTOS_DIR)/timers.o" -o "$@" "$<" 
#	@echo 'Finished building: $<'
#	@echo ' '



