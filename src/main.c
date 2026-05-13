#include <stdint.h>
#include <stdbool.h>

/* STM32L476xx specific definitions */
#define GPIOA_BASE    0x48000000U
#define RCC_BASE      0x40021000U

/* GPIO Port A */
volatile uint32_t *GPIOA_MODER = (uint32_t *)(GPIOA_BASE + 0x00U);
volatile uint32_t *GPIOA_PUPDR = (uint32_t *)(GPIOA_BASE + 0x0CU);
volatile uint32_t *GPIOA_ODR = (uint32_t *)(GPIOA_BASE + 0x14U);

/* Reset and Clock Control */
volatile uint32_t *RCC_AHB2ENR = (uint32_t *)(RCC_BASE + 0x4CU);

void SystemInit(void) {
    /* Enable GPIOA clock */
    *RCC_AHB2ENR |= (1U << 0U);
}

void gpio_init(void) {
    /* Configure PA5 as output (LED) */
    *GPIOA_MODER &= ~(3U << 10U);  /* Clear PA5 mode bits */
    *GPIOA_MODER |= (1U << 10U);   /* Set PA5 as output */
}

void led_on(void) {
    *GPIOA_ODR |= (1U << 5U);
}

void led_off(void) {
    *GPIOA_ODR &= ~(1U << 5U);
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0U; i < ms; i++) {
        for (uint32_t j = 0U; j < 8000U; j++) {
            __asm__("nop");
        }
    }
}

int main(void) {
    SystemInit();
    gpio_init();

    /* Main loop: blink LED */
    while (true) {
        led_on();
        delay_ms(500U);
        led_off();
        delay_ms(500U);
    }

    return 0;
}
