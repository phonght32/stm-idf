# Main Project Makefile 
# This Makefile is included directly from the user project Makefile in order to call the component.mk
# makefiles of all components (in a seperate make process) to build all libraries, then links them 
# together into the final file. 

.PHONY: build flash clean monitor help view_info

help:
	@echo "Welcom to STM-IDF. There are some make targets:"
	@echo ""
	@echo "make build - Build project"
	@echo "make clean - Remove all build output"
	@echo "make flash - Flash to stm32 targets via ST-LinkV2"
	@echo "make monitor - View log output"
	@echo ""
	@echo "Visit https://github.com/thanhphong98/stm-idf to see more details about STM-IDF or contribute"
	@echo "Visit https://github.com/thanhphong98/stm32-template to get project template"

# Default path of the project. Assume the Makefile is exist in current project directory.
ifndef PROJECT_PATH
PROJECT_PATH := $(abspath $(dir $(firstword $(MAKEFILE_LIST))))
export PROJECT_PATH
endif

# The directory where we put all binaries. The project Makefile can configure it if needed.
ifndef BUILD_DIR_BASE
	BUILD_DIR_BASE := $(PROJECT_PATH)/build
export BUILD_DIR_BASE
endif

# If no configure STM_IDF_PATH to variable environment, use stm-idf in current project. Assume
# current project contain stm-idf
ifndef STM_IDF_PATH
STM_IDF_PATH := $(PROJECT_PATH)/stm-idf
export STM_IDF_PATH
endif

# Component directory. The project Makefile can override these directory, or add extra component
# directory via EXTRA_COMPONENT_DIRS
ifndef COMPONENT_DIRS
EXTRA_COMPONENT_DIRS ?=
COMPONENT_DIRS := $(PROJECT_PATH)/components $(EXTRA_COMPONENT_DIRS) $(STM_IDF_PATH)/components $(PROJECT_PATH)/main
endif

# Make sure that every directory in the list is absulute path without trailing slash.
COMPONENT_DIRS := $(foreach cd,$(COMPONENT_DIRS),$(abspath $(cd)))
export COMPONENT_DIRS

# This is neccessary to split COMPONET_DIRS into SINGLE_COMPONET_DIRS and MULTI_COMPONENT_DIRS.
# List of component directories, i.e. directories which contain a component.mk file
SINGLE_COMPONENT_DIRS := $(abspath $(dir $(dir $(foreach cd, $(COMPONENT_DIRS), $(wildcard $(cd)/component.mk)))))
export SINGLE_COMPONENT_DIRS
# List of components directories, i.e. directories which may contain components
MULTI_COMPONENT_DIRS := $(filter-out $(SINGLE_COMPONENT_DIRS),$(COMPONENT_DIRS))

ifndef COMPONENTS
# Find all component names. The component names are the same as the
# directories they're in, so /bla/components/mycomponent/component.mk -> mycomponent.
# We need to do this for MULTI_COMPONENT_DIRS only, since SINGLE_COMPONENT_DIRS
# are already known to contain component.mk.
COMPONENTS := $(dir $(foreach cd,$(MULTI_COMPONENT_DIRS),$(wildcard $(cd)/*/component.mk))) $(SINGLE_COMPONENT_DIRS)
COMPONENTS := $(sort $(foreach comp,$(COMPONENTS),$(lastword $(subst /, ,$(comp)))))
endif
export COMPONENTS

# Resolve all of COMPONENTS into absolute paths in COMPONENT_PATHS.
# For each entry in COMPONENT_DIRS:
# - either this is directory with multiple components, in which case check that
#   a subdirectory with component name exists, and it contains a component.mk file.
# - or, this is a directory of a single component, in which case the name of this
#   directory has to match the component name
#
# If a component name exists in multiple COMPONENT_DIRS, we take the first match.
#
# NOTE: These paths must be generated WITHOUT a trailing / so we
# can use $(notdir x) to get the component name.
COMPONENT_PATHS := $(foreach comp,$(COMPONENTS),\
                        $(firstword $(foreach cd,$(COMPONENT_DIRS),\
                            $(if $(findstring $(cd),$(MULTI_COMPONENT_DIRS)),\
                                 $(abspath $(dir $(wildcard $(cd)/$(comp)/component.mk))),)\
                            $(if $(findstring $(cd),$(SINGLE_COMPONENT_DIRS)),\
                                 $(if $(filter $(comp),$(notdir $(cd))),$(cd),),)\
                   )))
export COMPONENT_PATHS

PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
CXX = $(GCC_PATH)/$(PREFIX)g++
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S



view_info:
	@echo $(COMPONENT_PATHS)
