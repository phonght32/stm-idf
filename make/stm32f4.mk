#Handle path prefix
STM_SERIES_PREFIX := stm32f4

ifeq ($(STM_LINE), STM32F407) 
STM_LINE_PREFIX := stm32f407
endif

ifeq ($(STM_TARGET), STM32F407VG) 
STM_TARGET_PREFIX := stm32f407vg
endif

ifeq ($(STM_LINE), STM32F405) 
STM_LINE_PREFIX := stm32f405
endif

ifeq ($(STM_TARGET), STM32F405RG) 
STM_TARGET_PREFIX := stm32f405rg
endif

# Build options
DEBUG = 1
OPT = -Og
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
AS_DEFS = 
C_DEFS +=  \
-DUSE_HAL_DRIVER \
-DSTM32F407xx \
-DSTM32F4_TARGET 