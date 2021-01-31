LIBNAME			= opencm3_stm32f1
DEFS			+= -DSTM32F1
FP_FLAGS		?= -msoft-float
ARCH_FLAGS		= -mthumb -mcpu=cortex-m3 $(FP_FLAGS) -mfix-cortex-m3-ldrd
DEVICE			= stm32f103c8
OOCD_INTERFACE 	?= stlink
OOCD_TARGET 	?= stm32f1x