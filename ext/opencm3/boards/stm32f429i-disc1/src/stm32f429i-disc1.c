#include <stm32f429i-disc1.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void system_board_setup(void)
{
    // Initialize leds
    rcc_periph_clock_enable(RCC_GPIOG);
    gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13 | GPIO14);
}

void system_led1_toggle()
{
    gpio_toggle(GPIOG, GPIO13);
}

void system_led1_on()
{
    gpio_set(GPIOG, GPIO13);
}

void system_led1_off()
{
    gpio_set(GPIOG, GPIO13);
}