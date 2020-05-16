# Check STM32 product series
ifeq ($(STM_SERIES), STM32F4) 
STM_SERIES_PREFIX := stm32f4
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
endif

ifeq ($(STM_SERIES), STM32F1) 
STM_SERIES_PREFIX := stm32f1
DEBUG = 1
OPT = -Og
CPU = -mcpu=cortex-m3
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
AS_DEFS = 
C_DEFS +=  \
-DUSE_HAL_DRIVER \
-DSTM32F103xB \
-DSTM32F1_TARGET 
endif

# Check STM32 product line
ifeq ($(STM_LINE), STM32F407) 
STM_LINE_PREFIX := stm32f407
endif

ifeq ($(STM_LINE), STM32F103) 
STM_LINE_PREFIX := stm32f103
endif

# Check STM32 target 
ifeq ($(STM_TARGET), STM32F407VG) 
STM_TARGET_PREFIX := stm32f407vg
endif

ifeq ($(STM_TARGET), STM32F103C8) 
STM_TARGET_PREFIX := stm32f103c8
endif

# Handle specify STM32 target.
HAL_DRIVER_PATH := $(STM_IDF_PATH)/components/hal_driver

SOURCE_PATHS += \
$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/src \
$(STM_IDF_PATH)/components/stm32_private/$(STM_SERIES_PREFIX) \
$(STM_IDF_PATH)/components/stm32_private/$(STM_SERIES_PREFIX)/$(STM_LINE_PREFIX) \
$(STM_IDF_PATH)/components/startup/$(STM_SERIES_PREFIX)/$(STM_LINE_PREFIX) \
$(STM_IDF_PATH)/components/freertos/portable/$(STM_SERIES_PREFIX)/memmang \
$(STM_IDF_PATH)/components/freertos/portable/$(STM_SERIES_PREFIX)/gcc/arm_cmf

INCLUDE_PATHS += \
-I$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/inc \
-I$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/inc/Legacy \
-I$(STM_IDF_PATH)/components/driver/private/$(STM_SERIES_PREFIX)/include \
-I$(STM_IDF_PATH)/components/cmsis/device/stm32/$(STM_SERIES_PREFIX)/inc \
-I$(STM_IDF_PATH)/components/freertos/portable/$(STM_SERIES_PREFIX)/gcc/arm_cmf

