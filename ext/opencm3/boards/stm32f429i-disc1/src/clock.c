#include <stdio.h>
#include <ctype.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>

static volatile uint32_t system_millis;
static volatile uint32_t delay_timer;

void sys_tick_handler(void);

void sys_tick_handler(void)
{
	system_millis++;
	if (delay_timer > 0) {
		delay_timer--;
	}
}

void system_clock_enable(void)
{
	rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	/* set up the SysTick function (1mS interrupts) */
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	STK_CVR = 0;
	systick_set_reload(rcc_ahb_frequency / 1000);
	systick_counter_enable();
	systick_interrupt_enable();
}

void system_delay(uint32_t delay)
{
	delay_timer = delay;
	while (delay_timer);
}
