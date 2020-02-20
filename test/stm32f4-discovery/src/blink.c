#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void delay(void);

void delay(void)
{
	int i;

	for (i = 0; i < 4000000; i++)
		__asm__("nop");
}

int main(void)
{
	rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
	rcc_periph_clock_enable(RCC_GPIOD);

	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
	gpio_clear(GPIOD, GPIO13 | GPIO15);
	gpio_set(GPIOD, GPIO12 | GPIO14);

	while (1)
	{
		gpio_toggle(GPIOD, GPIO12 | GPIO13 | GPIO14 | GPIO15);
		delay();
	}

	return 0;
}
