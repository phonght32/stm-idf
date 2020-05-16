# Handle path prefix
STM_SERIES_PREFIX := stm32f1

ifeq ($(STM_LINE), STM32F103) 
STM_LINE_PREFIX := stm32f103
endif

ifeq ($(STM_TARGET), STM32F103C8) 
STM_TARGET_PREFIX := stm32f103c8
endif

# Build options
DEBUG = 1
OPT = -Og
CPU = -mcpu=cortex-m3
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
AS_DEFS = 
C_DEFS +=  \
-DUSE_HAL_DRIVER \
-DSTM32F103xG \
-DSTM32F1_TARGET 