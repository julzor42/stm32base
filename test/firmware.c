#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void delay(void);
void board_setup(void);

void delay(void)
{
	int i;

	for (i = 0; i < 1200000; i++)
		__asm__("nop");
}

void board_setup(void)
{
    rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
    rcc_periph_clock_enable(RCC_GPIOG);

    gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13 | GPIO14);

    gpio_set(GPIOG, GPIO13);
}

int main(void)
{
	board_setup();

	while (1)
	{
		gpio_toggle(GPIOG, GPIO13 | GPIO14);
		delay();
	}

	return 0;
}
