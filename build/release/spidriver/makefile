##################################
#															 #
# Makefile - entertainment_IPS   #
#															 #
# 	System - efm32zg222f32       #
#				OS - FreeRTOS            #
#															 #
#		Author - Aidan Millar Powell #
#		 Alias - MedicineMan25       #
#															 #
##################################

SOURCE_DIR=../../../src
DEP_LIST_OUT=./CMSIS/efm32zg/system_efm32zg.d

PROJECT_NAME=theseus
TARGET=$(PROJECT_NAME)-spidriver.bin 


#################################
# 			    LIB	
#################################

PROJECT_LIB_DIR=../../../lib
LOCAL_LIB_DIR=/usr/lib
GCC_LIB=/usr/lib/gcc/x86_64-pc-linux-gnu/9.2.0

#################################
# 			    INCLUDE	
#################################

PROJECT_INCLUDE_DIR= \
-I../../../include

GCC_INCLUDE= \
-I$(GCC_LIB)/include \
-I$(GCC_LIB)/include-fixed

PROJECT_INCLUDE= \
-I$(SOURCE_DIR)/HAL/slave/dw1000 \
-I$(SOURCE_DIR)/HAL/slave/venus638 \
-I$(SOURCE_DIR)/application/app_fns \
-I$(SOURCE_DIR)/application/configs \
-I$(SOURCE_DIR)/port_adaptors \
-I$(SOURCE_DIR)/middleware \

INCLUDE= \
$(GCC_INCLUDE) \
$(PROJECT_INCLUDE) \
$(PROJECT_INCLUDE_DIR) 

#################################
# 			    SOURCES	
#################################

#FREERTOS_SOURCES= \
$(FREERTOS_DIR)/Source/*.c

PROJECT_SOURCES= \
$(wildcard $(SOURCE_DIR)/HAL/slave/dw1000/*.c) \
$(wildcard $(SOURCE_DIR)/HAL/slave/venus638/*.c) \
$(wildcard $(SOURCE_DIR)/middleware/*.c) \
$(SOURCE_DIR)/application/configs/config_spidriver.c \
$(SOURCE_DIR)/application/configs/config_dw1000.c \
$(wildcard $(SOURCE_DIR)/application/*.c) \
$(SOURCE_DIR)/port_adaptors/dw1000_adaptor.c \
$(SOURCE_DIR)/port_adaptors/spidriver_adaptor.c


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
# 			  DIRECTORIES 	
#################################

GCC_LIB=/usr/lib/gcc/x86_64-pc-linux-gnu/9.2.0

SRC_DIR = \
$(PROJECT_SOURCES)

BUILD_DIR=.


#################################
# 		    BUILD FLAGS 				  	
#################################

CC=gcc
LD=$(CC)

CFLAGS= -g '-DSPIDRIVER=1' '-DDW1000=1' '-DVENUS638=1' $(INCLUDE) -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections

LDFLAGS= \
 -L$(GCC_LIB) \
 -L$(LOCAL_LIB_DIR) \
 -lspidriver -v -g -gdwarf-2 -Xlinker --gc-sections


#################################
#        BUILD TARGET 				  
#################################

target: $(TARGET)
	size "$(PROJECT_NAME)-spidriver.bin"

$(TARGET): obj
	$(LD) -o $@ $(wildcard $(BUILD_DIR)/*.o) $(LDFLAGS)

obj: $(SRC_DIR)
	$(CC) $(CFLAGS) $^

#clean:
#	rm $(TARGET) $(OBJECTS)

clean:
	rm $(TARGET) $(BUILD_DIR)/*.o $(PROJECT_NAME).hex $(PROJECT_NAME).bin CMSIS/efm32zg/system_efm32zg.d
.PHONY: target all clean assembly
