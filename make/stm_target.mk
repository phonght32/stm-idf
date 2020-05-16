# Check STM32 product series
ifeq ($(STM_SERIES), STM32F4) 
include $(STM_IDF_PATH)/make/stm32f4.mk
endif

ifeq ($(STM_SERIES), STM32F1) 
include $(STM_IDF_PATH)/make/stm32f1.mk
endif

# Handle specify STM32 target.
HAL_DRIVER_PATH := $(STM_IDF_PATH)/components/hal_driver

SOURCE_PATHS += \
$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/src \
$(STM_IDF_PATH)/components/stm32_private/$(STM_SERIES_PREFIX) \
$(STM_IDF_PATH)/components/stm32_private/$(STM_SERIES_PREFIX)/$(STM_LINE_PREFIX) \
$(STM_IDF_PATH)/components/startup/$(STM_SERIES_PREFIX)/$(STM_LINE_PREFIX) \
$(STM_IDF_PATH)/components/freertos/portable/$(STM_SERIES_PREFIX)/memmang \
$(STM_IDF_PATH)/components/freertos/portable/$(STM_SERIES_PREFIX)/gcc/arm_cmf \
$(STM_IDF_PATH)/components/driver/$(STM_SERIES_PREFIX)

INCLUDE_PATHS += \
-I$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/inc \
-I$(HAL_DRIVER_PATH)/$(STM_SERIES_PREFIX)/inc/Legacy \
-I$(STM_IDF_PATH)/components/cmsis/device/stm32/$(STM_SERIES_PREFIX)/inc \
-I$(STM_IDF_PATH)/components/freertos/portable/$(STM_SERIES_PREFIX)/gcc/arm_cmf \
-I$(STM_IDF_PATH)/components/driver/$(STM_SERIES_PREFIX)/include

