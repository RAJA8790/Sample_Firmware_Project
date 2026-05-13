/**
 * @file main.c
 * @brief Main firmware entry point for ARM Cortex-M4 microcontroller
 * @author Firmware Team
 * @version 1.0.0
 */

#include "main.h"
#include "utils.h"
#include <stdint.h>

/**
 * @brief System clock frequency in Hz
 */
#define SYSTEM_CLOCK_HZ 80000000U

/**
 * @brief LED GPIO port address (example: GPIO Port F)
 */
#define LED_PORT_BASE 0x40025000U
#define LED_PIN 3U

/**
 * @brief Initialize system clock
 * @return Status code (0 = success)
 */
static int32_t init_system_clock(void)
{
    /* Configure PLL for 80 MHz operation */
    volatile uint32_t *sysctl = (volatile uint32_t *)0x400FE000U;
    
    /* Enable main oscillator */
    sysctl[0x06] |= 0x10U;  /* MOSCDIS bit */
    
    /* Wait for oscillator to stabilize */
    uint32_t timeout = 10000U;
    while ((timeout > 0U) && ((sysctl[0x0A] & 0x01U) == 0U))
    {
        timeout--;
    }
    
    return (timeout > 0U) ? 0 : -1;
}

/**
 * @brief Initialize GPIO for LED control
 * @return Status code (0 = success)
 */
static int32_t init_gpio(void)
{
    volatile uint32_t *gpio_port = (volatile uint32_t *)LED_PORT_BASE;
    
    /* Configure LED pin as output */
    gpio_port[0x04] |= (1U << LED_PIN);  /* GPIO direction register */
    
    return 0;
}

/**
 * @brief Toggle LED state
 */
static void toggle_led(void)
{
    volatile uint32_t *gpio_port = (volatile uint32_t *)LED_PORT_BASE;
    gpio_port[0x00] ^= (1U << LED_PIN);  /* GPIO data register */
}

/**
 * @brief Simple delay function
 * @param milliseconds Delay duration in milliseconds
 */
static void delay_ms(uint32_t milliseconds)
{
    volatile uint32_t count = (SYSTEM_CLOCK_HZ / 3000U) * milliseconds;
    while (count > 0U)
    {
        count--;
    }
}

/**
 * @brief Main firmware entry point
 * @return Exit code
 */
int32_t main(void)
{
    /* Initialize hardware */
    if (init_system_clock() != 0)
    {
        return -1;
    }
    
    if (init_gpio() != 0)
    {
        return -1;
    }
    
    /* Main event loop */
    while (1)
    {
        toggle_led();
        delay_ms(500U);
    }
    
    return 0;
}
