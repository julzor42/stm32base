#ifndef _STM32F429IDISC1_H_
#define  _STM32F429IDISC1_H_

#include <stdio.h>

// setup
void system_board_setup(void);
void system_clock_enable(void);

// timing
void system_delay(uint32_t ms);

// leds
void system_led1_toggle(void);
void system_led1_on(void);
void system_led1_off(void);

// usart
void system_usart_init(void);

// lcd
void lcd_init(void);
void lcd_show_frame(void);
void lcd_draw_pixel(int x, int y, uint16_t color);

/* Color definitions */
#define	LCD_BLACK   0x0000
#define	LCD_BLUE    0x1F00
#define	LCD_RED     0x00F8
#define	LCD_GREEN   0xE007
#define LCD_CYAN    0xFF07
#define LCD_MAGENTA 0x1FF8
#define LCD_YELLOW  0xE0FF
#define LCD_WHITE   0xFFFF
#define LCD_GREY    0xc339

#define LCD_WIDTH   240
#define LCD_HEIGHT  320

// sdram
#define SDRAM_BASE_ADDRESS ((uint8_t *)(0xd0000000))

/* Initialize the SDRAM chip on the board */
void sdram_init(void);

int main(void);

#endif /* _STM32F429IDISC1_H_ */
