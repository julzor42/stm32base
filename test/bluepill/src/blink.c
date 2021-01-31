#include <bluepill.h>

int main()
{
    bluepill_board_setup();
    bluepill_clock_enable();

    while (1)
    {
        bluepill_led_on();
        bluepill_delay(50);

        bluepill_led_off();
        bluepill_delay(1000);
    }

    return 0;
}
