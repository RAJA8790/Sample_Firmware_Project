/*
 * Firmware Sample Project
 * Target: ARM Cortex-M (STM32-like)
 * Description: LED blink with button input
 */

#include "led.h"
#include "button.h"
#include "system.h"
#include <stdint.h>

#define BLINK_DELAY_MS  500
#define VERSION_MAJOR   1
#define VERSION_MINOR   0
#define VERSION_PATCH   0

int main(void)
{
    /* Initialize hardware */
    system_init();
    led_init();
    button_init();

    uint8_t led_state = LED_OFF;
    uint32_t tick     = 0;

    /* Main loop */
    while (1)
    {
        /* Toggle LED every BLINK_DELAY_MS */
        if (system_get_tick() - tick >= BLINK_DELAY_MS)
        {
            led_state = (led_state == LED_OFF) ? LED_ON : LED_OFF;
            led_set(LED_GREEN, led_state);
            tick = system_get_tick();
        }

        /* If button pressed, turn on red LED */
        if (button_is_pressed(BUTTON_USER))
        {
            led_set(LED_RED, LED_ON);
        }
        else
        {
            led_set(LED_RED, LED_OFF);
        }
    }

    return 0;
}
