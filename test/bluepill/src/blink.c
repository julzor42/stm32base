#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <bluepill.h>

void delay(void);

void delay(void)
{
	int i;

	for (i = 0; i < 800000; i++)
		__asm__("nop");
}

int main(void)
{
	bluepill_setup();

	bluepill_led_off();

	while (1)
	{
		bluepill_led_toggle();
		delay();
	}

	return 0;
}
