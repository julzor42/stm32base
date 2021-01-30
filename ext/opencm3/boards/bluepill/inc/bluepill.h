#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdio.h>

// setup
void bluepill_board_setup(void);
void bluepill_clock_enable(void);

// gpio
void bluepill_led_on(void);
void bluepill_led_off(void);
void bluepill_led_toggle(void);

// timing
void bluepill_delay(uint32_t ms);

int main(void);

#endif /* _BOARD_H_ */
