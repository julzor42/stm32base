LIBNAME			= opencm3_stm32f4
DEFS			+= -DSTM32F4
FP_FLAGS		?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS		= -mthumb -mcpu=cortex-m4 $(FP_FLAGS)
DEVICE			= stm32f429zit6u
OOCD_INTERFACE 	?= stlink
OOCD_TARGET 	?= stm32f4x