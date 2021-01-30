# Default values
OPENCM3_DIR 	?= /opt/libopencm3
OOCD_INTERFACE 	?= stlink
OOCD_TARGET 	?= stm32f1x
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

program: $(PROJECT).elf
	@printf "  FLASH\t$<\n"
	$(Q)(echo "halt; program $(realpath $(*).elf) verify reset" | nc -4 localhost 4444 2>/dev/null) || \
		$(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
		-f target/$(OOCD_TARGET).cfg \
		-c "program $(realpath $(*).elf) verify reset exit" \
		$(NULL)
