ifeq ($(STM_SERIES), STM32F4) 
STM_SERIES_PREFIX := stm32f4
C_DEFS += -DSTM32F4_TARGET
endif

ifeq ($(STM_LINE), STM32F407) 
STM_LINE_PREFIX := stm32f407
endif

ifeq ($(STM_TARGET), STM32F407VG) 
STM_TARGET_PREFIX := stm32f407vg
endif

# Handle specify STM32 target.
HAL_DRIVER_PATH := $(STM_IDF_PATH)/components/hal_driver

SOURCE_PATHS += \
$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/src \
$(STM_IDF_PATH)/components/stm32_private/$(STM_SERIES_PREFIX) \
$(STM_IDF_PATH)/components/stm32_private/$(STM_SERIES_PREFIX)/$(STM_LINE_PREFIX) \
$(STM_IDF_PATH)/components/startup/$(STM_SERIES_PREFIX)/$(STM_LINE_PREFIX)

INCLUDE_PATHS += \
-I$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/inc \
-I$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/inc/Legacy \
-I$(STM_IDF_PATH)/components/driver/private/$(STM_SERIES_PREFIX)/include \
-I$(STM_IDF_PATH)/components/cmsis/device/stm32/$(STM_SERIES_PREFIX)/include 

