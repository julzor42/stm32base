# Default values
OPENCM3_DIR 	?= /opt/libopencm3
DEBUGPORT 		?= 4242
DEBUGIP 		?= 
DEBUGTARGET 	?= extended-remote $(DEBUGIP):$(DEBUGPORT)

# Project default configuration
CFILES 			?= $(wildcard src/*.c)
CFLAGS 			?=-I./inc
PROJECT 		?= firmware

# Board specific source files
CFILES  		+= $(wildcard $(BOARD_PATH)/src/*.c)
CFLAGS 			+=-I$(BOARD_PATH)/inc

# Board profile
EXTPATH 		?= ext
CM3BASE 		?= $(EXTPATH)/opencm3
BOARDS_BASEPATH ?= $(CM3BASE)/boards
BOARD_PATH 		 = $(BOARDS_BASEPATH)/$(BOARD)

include $(BOARD_PATH)/board.mk

LDSCRIPT ?= $(BOARD_PATH)/board.ld

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
include $(OPENCM3_DIR)/tests/rules.mk

re: clean all

debug:
	gdb -quiet $(PROJECT).elf -ex "target $(DEBUGTARGET)" -ex="set confirm off" -ex load #-ex continue
	