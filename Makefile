#/*
# * Copyright (C) 2017 Wang Ge
# *
# * This program is free software: you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation, in version 3.
# *
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with this program. If not, see <http://www.gnu.org/licenses/>.
# */

#-----------------------------------------------------------------------------
# project name
#
PROJECT     := bldc-controller

#-----------------------------------------------------------------------------
# project directories
#

# list of all source directories used by this project
VPATH = \
	source/bsp/source \
	source/bsp/source/mcc_generated_files \
	source/qpc/src/qf \
	source/qpc/src/qk \
	source/lib/freemodbus/modbus \
	source/lib/freemodbus/modbus/rtu \
	source/lib/freemodbus/modbus/functions \
	source/lib/freemodbus/ports/dsPICDEM_MCLV-2 \
	source/utils/source \
	source/system/source \
	source/blinky/source \
	source/modbus/source \
	source/motor_ctrl/source

# list of all include directories needed by this project
INCLUDES  = \
	-Isource/bsp/include \
	-Isource/qpc/include \
	-Isource/qpc/src \
	-Isource/qpc/ports/pic24_dspic/qk \
	-Isource/lib/freemodbus/modbus/include \
	-Isource/lib/freemodbus/modbus/rtu \
	-Isource/lib/freemodbus/ports/dsPICDEM_MCLV-2 \
	-Isource/utils/include \
	-Isource/system/include \
	-Isource/blinky/include \
	-Isource/modbus/include \
	-Isource/modbus/source \
	-Isource/motor_ctrl/include

#-----------------------------------------------------------------------------
# files
#

# Assembler source files
ASM_SRCS :=

# C source files
C_SRCS := \
	main.c \
	blinky.c \
	modbus.c

# C++ source files
#CPP_SRCS :=

QP_SRCS := \
	qep_hsm.c \
	qep_msm.c \
	qf_act.c \
	qf_actq.c \
	qf_defer.c \
	qf_dyn.c \
	qf_mem.c \
	qf_ps.c \
	qf_qact.c \
	qf_qeq.c \
	qf_qmact.c \
	qf_time.c \
	qk.c \
	qk_mutex.c

FREEMODEBUS_SRCS := \
	mb.c \
	mbrtu.c \
	mbfunccoils.c \
	mbfuncdiag.c \
	mbfuncdisc.c \
	mbfuncholding.c \
	mbfuncinput.c \
	mbfuncother.c \
	mbutils.c \
	portcrc.c \
	portevent.c \
	portserial.c \
	porttimer.c

BSP_SRCS := \
	bsp.c \
	crc.c \
	interrupt_manager.c \
	mcc.c \
	pin_manager.c \
	tmr1.c \
	tmr2.c \
	traps.c

# Library files and directories
LIBS     :=
LIB_DIRS :=

# Linker script files
LD_SCRIPT := scripts/p33EP256MC506.gld

# defines
DEFINES   :=

# PIC_MCU type
PIC_MCU=33EP256MC506

#-----------------------------------------------------------------------------
# XC16 toolset (NOTE: You need to adjust to your machine)
# see http://www.microchip.com/mplab/compilers
#
ifeq ($(GNU_PIC30),)
GNU_PIC30 = C:\Program Files\Microchip\xc16\v1.31
endif

# make sure that the XC16 toolset exists...
ifeq ("$(wildcard $(GNU_PIC30))","")
$(error GNU_PIC30 toolset not found. Please adjust the Makefile)
endif

CC   := $(GNU_PIC30)/bin/xc16-gcc
CPP  := $(GNU_PIC30)/bin/xc16-gcc
AS   := $(GNU_PIC30)/bin/xc16-as
LINK := $(GNU_PIC30)/bin/xc16-gcc
HEX  := $(GNU_PIC30)/bin/xc16-bin2hex

##############################################################################
# Typically, you should not need to change anything below this line

#-----------------------------------------------------------------------------
# basic utilities (included in Qtools for Windows), see:
#    http://sourceforge.net/projects/qpc/files/Qtools
MKDIR := mkdir
RM    := rm

#------------------------------------------------------------------------------
# build options for various configurations for Microchip PIC24/dsPIC
#

# combine all the soruces...
C_SRCS += $(QP_SRCS) $(BSP_SRCS) $(FREEMODEBUS_SRCS)

# ifeq (debug, $(CONF)) # Debug configuration ...................................
BUILD_DIR := build/debug

ASFLAGS = -mcpu=$(PIC_MCU) -omf=elf -DXPRJ_default=default -no-legacy-libc \
          -Wa --defsym=__MPLAB_BUILD=1 -g --no-relax

CFLAGS = -mcpu=$(PIC_MCU) -mno-eds-warn -g -omf=elf -DXPRJ_default=default -legacy-libc -O0 $(INCLUDES) -msmart-io=1 -Wall -msfr-warn=off -ffunction-sections -fdata-sections
# else
# endif  # ......................................................................

LINKFLAGS = -mcpu=$(PIC_MCU) -omf=elf -DXPRJ_default=default -legacy-libc -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--script=$(LD_SCRIPT),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="$(BUILD_DIR)/$(PROJECT).map"

ASM_OBJS     := $(patsubst %.s,%.o,  $(notdir $(ASM_SRCS)))
C_OBJS       := $(patsubst %.c,%.o,  $(notdir $(C_SRCS)))

TARGET_HEX   := $(BUILD_DIR)/$(PROJECT).hex
TARGET_ELF   := $(BUILD_DIR)/$(PROJECT).elf
ASM_OBJS_EXT := $(addprefix $(BUILD_DIR)/, $(ASM_OBJS))
C_OBJS_EXT   := $(addprefix $(BUILD_DIR)/, $(C_OBJS))
C_DEPS_EXT   := $(patsubst %.o, %.d, $(C_OBJS_EXT))

# create $(BUILD_DIR) if it does not exist
ifeq ("$(wildcard $(BUILD_DIR))","")
$(shell $(MKDIR) -p $(BUILD_DIR))
endif

#-----------------------------------------------------------------------------
# rules
#

all: $(TARGET_HEX)
# all: $(TARGET_ELF)

$(TARGET_HEX): $(TARGET_ELF)
	$(HEX) $< -omf=elf

$(TARGET_ELF) : $(ASM_OBJS_EXT) $(C_OBJS_EXT)
	$(LINK) -o $@ $^ $(LIBS) $(LINKFLAGS)

$(BUILD_DIR)/%.d : %.c
	$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $< > $@

$(BUILD_DIR)/%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# include dependency files only if our goal depends on their existence
ifneq ($(MAKECMDGOALS),clean)
  ifneq ($(MAKECMDGOALS),show)
-include $(C_DEPS_EXT)
  endif
endif

.PHONY : clean
clean:
	-$(RM) $(BUILD_DIR)/*.o \
	$(BUILD_DIR)/*.d \
	$(BUILD_DIR)/*.hex \
	$(BUILD_DIR)/*.elf \
	$(BUILD_DIR)/*.map

show:
	@echo PROJECT = $(PROJECT)
	@echo CONF = $(CONF)
	@echo DEFINES = $(DEFINES)
	@echo ASM_SRCS = $(ASM_SRCS)
	@echo C_SRCS = $(C_SRCS)
	@echo ASM_OBJS_EXT = $(ASM_OBJS_EXT)
	@echo C_OBJS_EXT = $(C_OBJS_EXT)
	@echo C_DEPS_EXT = $(C_DEPS_EXT)
	@echo TARGET_ELF = $(TARGET_ELF)
