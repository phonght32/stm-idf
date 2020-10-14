#Handle path prefix
STM_SERIES_PREFIX := stm32f4

################################################################################
# STM32F401
################################################################################
ifeq ($(STM_LINE), STM32F401) 
STM_LINE_PREFIX := stm32f401
endif

ifeq ($(STM_TARGET), STM32F401CB) 
STM_TARGET_PREFIX := stm32f401cb
endif


################################################################################
# STM32F405 
################################################################################
ifeq ($(STM_LINE), STM32F405) 
STM_LINE_PREFIX := stm32f405
endif

ifeq ($(STM_TARGET), STM32F405RG) 
STM_TARGET_PREFIX := stm32f405rg
endif


################################################################################
# STM32F407
################################################################################
ifeq ($(STM_LINE), STM32F407) 
STM_LINE_PREFIX := stm32f407
endif

ifeq ($(STM_TARGET), STM32F407VG) 
STM_TARGET_PREFIX := stm32f407vg
endif


################################################################################
# STM32F446
################################################################################
ifeq ($(STM_LINE), STM32F446) 
STM_LINE_PREFIX := stm32f446
endif

ifeq ($(STM_TARGET), STM32F446RE) 
STM_TARGET_PREFIX := stm32f446re
endif

ifeq ($(STM_TARGET), STM32F446ZE) 
STM_TARGET_PREFIX := stm32f446ze
endif

STM_TARGET_HAL := $(STM_LINE)xx

ifeq ($(STM_TARGET), STM32F401CB)
STM_TARGET_HAL := STM32F401xC
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
-DSTM32F4_TARGET \
-D$(STM_TARGET_HAL)
