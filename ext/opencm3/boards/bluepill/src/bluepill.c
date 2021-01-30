#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <bluepill.h>

void bluepill_board_setup()
{
	rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);

	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
}

void bluepill_led_on()
{
	gpio_clear(GPIOC, GPIO13);
}

void bluepill_led_off()
{
	gpio_set(GPIOC, GPIO13);
}

void bluepill_led_toggle()
{
	gpio_toggle(GPIOC, GPIO13);
}
