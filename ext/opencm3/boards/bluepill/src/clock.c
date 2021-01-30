#include <libopencm3/cm3/systick.h>
#include <bluepill.h>

static volatile uint32_t system_millis;
static volatile uint32_t delay_timer;

void sys_tick_handler(void);

void sys_tick_handler(void)
{
    system_millis++;
    if (delay_timer > 0)
    {
        delay_timer--;
    }
}

void bluepill_clock_enable(void)
{
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8); // 72M/8 = 9M
    systick_set_reload(8999);                            // 9M / 9000 = 1k => T = 1ms
    systick_interrupt_enable();
    systick_counter_enable();
}

void bluepill_delay(uint32_t delay)
{
    delay_timer = delay;
    while (delay_timer)
        ;
}