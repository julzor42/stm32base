#include <stm32f429i-disc1.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

void uart_putc(char c);
int _write(int fd, char *ptr, int len);

void system_usart_init()
{
    /* Setup GPIO A pins for the USART1 function */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART1);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);

    usart_set_baudrate(USART1, 115200);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_mode(USART1, USART_MODE_TX_RX);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
    usart_enable(USART1);
}

/*
 * uart_putc
 *
 * This pushes a character into the transmit buffer for
 * the channel and turns on TX interrupts (which will fire
 * because initially the register will be empty.) If the
 * ISR sends out the last character it turns off the transmit
 * interrupt flag, so that it won't keep firing on an empty
 * transmit buffer.
 */
void uart_putc(char c)
{

    while ((USART_SR(USART1) & USART_SR_TXE) == 0)
        ;
    USART_DR(USART1) = c;
}

/*
 * Called by libc stdio functions
 */
int _write(int fd, char *ptr, int len)
{
    int i = 0;

    /*
	 * Write "len" of char from "ptr" to file id "fd"
	 * Return number of char written.
	 */
    if (fd > 2)
    {
        return -1; /* STDOUT, STDIN, STDERR */
    }
    while (*ptr && (i < len))
    {
        uart_putc(*ptr);
        if (*ptr == '\n')
        {
            uart_putc('\r');
        }
        i++;
        ptr++;
    }
    return i;
}
