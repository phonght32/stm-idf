# Handle path prefix
STM_SERIES_PREFIX := stm32l4

################################################################################
# STM32L4R5
################################################################################
ifeq ($(STM_LINE), STM32L4R5) 
STM_LINE_PREFIX := stm32l4r5
endif

ifeq ($(STM_TARGET), STM32L4R5ZI) 
STM_TARGET_PREFIX := stm32l4r5zi
STM_TARGET_HAL := STM32L4R5xx
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
-DSTM32L4_TARGET \
-D$(STM_TARGET_HAL)