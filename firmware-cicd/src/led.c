#include "led.h"
#include <stdint.h>
#include <string.h>

/* Internal state store for all LEDs */
static led_state_t led_states[3] = { LED_OFF, LED_OFF, LED_OFF };

/*
 * led_init
 * Initialise all LEDs to OFF state
 */
void led_init(void)
{
    memset(led_states, LED_OFF, sizeof(led_states));

    /*
     * In real hardware you would configure GPIO pins here.
     * Example for STM32:
     *   RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
     *   GPIOD->MODER |= GPIO_MODER_MODER12_0;
     */
}

/*
 * led_set
 * Set a specific LED to ON or OFF
 */
void led_set(led_id_t led, led_state_t state)
{
    if (led > LED_BLUE) return;

    led_states[led] = state;

    /*
     * In real hardware you would write to GPIO here.
     * Example for STM32:
     *   if (state == LED_ON)
     *       GPIOD->BSRR = (1 << pin);
     *   else
     *       GPIOD->BSRR = (1 << (pin + 16));
     */
}

/*
 * led_get
 * Read back the current state of an LED
 */
led_state_t led_get(led_id_t led)
{
    if (led > LED_BLUE) return LED_OFF;
    return led_states[led];
}

/*
 * led_toggle
 * Flip the current state of an LED
 */
void led_toggle(led_id_t led)
{
    if (led > LED_BLUE) return;
    led_states[led] = (led_states[led] == LED_OFF) ? LED_ON : LED_OFF;
}

/*
 * led_all_off
 * Turn off all LEDs
 */
void led_all_off(void)
{
    for (int i = 0; i <= LED_BLUE; i++)
    {
        led_set((led_id_t)i, LED_OFF);
    }
}
