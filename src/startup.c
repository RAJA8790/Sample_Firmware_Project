#include <stdint.h>

/* Linker-provided symbols */
extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _stack;

/* Forward declarations */
int main(void);
void SystemInit(void);

/* Default interrupt handlers */
void Default_Handler(void) {
    while (1) {
        __asm__("nop");
    }
}

void Reset_Handler(void) {
    /* Copy initialized data from FLASH to RAM */
    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;

    // cppcheck-suppress comparePointers
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* Initialize BSS section to zero */
    dst = &_sbss;
    // cppcheck-suppress comparePointers
    while (dst < &_ebss) {
        *dst++ = 0U;
    }

    /* Initialize system */
    SystemInit();

    /* Call main */
    main();

    /* Hang if main returns */
    while (1) {
        __asm__("nop");
    }
}
