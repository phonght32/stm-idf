##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.5.2] date: [Sun Mar 29 22:53:47 ICT 2020] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------
include stm-idf/make/project_dir.mk
######################################
# target
######################################
TARGET = $(PROJECT_NAME)


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
main/main.c \
main/stm32f4xx_it.c \
main/system_stm32f4xx.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_adc.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_adc_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_can.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_cec.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_cortex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_crc.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_cryp.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_cryp_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dac.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dac_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dcmi.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dcmi_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dfsdm.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dma.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dma2d.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dma_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_dsi.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_eth.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_exti.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_flash.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_flash_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_flash_ramfunc.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_fmpi2c.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_fmpi2c_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_gpio.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_hash.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_hash_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_hcd.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_i2c.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_i2c_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_i2s.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_i2s_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_irda.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_iwdg.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_lptim.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_ltdc.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_ltdc_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_mmc.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_msp_template.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_nand.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_nor.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_pccard.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_pcd.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_pcd_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_pwr.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_pwr_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_qspi.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_rcc.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_rng.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_rtc.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_rtc_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_sai.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_sai_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_sd.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_sdram.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_smartcard.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_smbus.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_spdifrx.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_spi.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_sram.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_tim.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_tim_ex.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_uart.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_usart.c \
$(STM32F4XX_HAL_PATH)/src/stm32f4xx_hal_wwdg.c \
$(RTOS_PATH)/croutine.c \
$(RTOS_PATH)/event_groups.c \
$(RTOS_PATH)/list.c \
$(RTOS_PATH)/queue.c \
$(RTOS_PATH)/stream_buffer.c \
$(RTOS_PATH)/tasks.c \
$(RTOS_PATH)/timers.c \
$(RTOS_PATH)/portable/memmang/heap_4.c \
$(RTOS_PATH)/portable/gcc/arm_cm4f/port.c \
$(CMSIS_RTOS_PATH)/cmsis_os.c \
$(IDF_COMPONENT_PATH)/stm32/panic.c \

# ASM sources
ASM_SOURCES =  \
startup_stm32f407xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F407xx


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-Imain/inc \
-I$(STM32F4XX_HAL_PATH)/inc \
-I$(STM32F4XX_HAL_PATH)/inc/Legacy \
-I$(CMSIS_PATH)/Device/ST/STM32F4xx/Include \
-I$(CMSIS_PATH)/Include \
-I$(CMSIS_PATH)/Include \
-I$(RTOS_PATH)/include \
-I$(RTOS_PATH)/include/freertos \
-I$(CMSIS_RTOS_PATH) \
-I$(RTOS_PATH)/portable/gcc/arm_cm4f


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = stm-idf/make/stm32f4xx_flash.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
