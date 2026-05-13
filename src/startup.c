/**
 * @file startup.c
 * @brief ARM Cortex-M4 startup code and exception handlers
 * @author Firmware Team
 * @version 1.0.0
 */

#include <stdint.h>
#include <string.h>

/**
 * @brief Extern declarations for linker symbols
 */
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _data_load;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern int32_t main(void);

/**
 * @brief Default exception handler
 */
void default_handler(void)
{
    while (1)
    {
        /* Infinite loop - exception occurred */
    }
}

/**
 * @brief Reset handler - called on power-up or reset
 */
void reset_handler(void)
{
    uint32_t *src, *dst;
    
    /* Copy initialized data from flash to RAM */
    src = &_data_load;
    dst = &_data_start;
    while (dst < &_data_end)
    {
        *dst++ = *src++;
    }
    
    /* Zero-fill the BSS section */
    dst = &_bss_start;
    while (dst < &_bss_end)
    {
        *dst++ = 0U;
    }
    
    /* Call main function */
    main();
    
    /* Trap if main returns */
    default_handler();
}

/**
 * @brief NMI handler
 */
void nmi_handler(void)
{
    default_handler();
}

/**
 * @brief Hard fault handler
 */
void hard_fault_handler(void)
{
    default_handler();
}

/**
 * @brief Memory management fault handler
 */
void mem_fault_handler(void)
{
    default_handler();
}

/**
 * @brief Bus fault handler
 */
void bus_fault_handler(void)
{
    default_handler();
}

/**
 * @brief Usage fault handler
 */
void usage_fault_handler(void)
{
    default_handler();
}

/**
 * @brief SVC handler
 */
void svc_handler(void)
{
    default_handler();
}

/**
 * @brief Debug monitor handler
 */
void debug_mon_handler(void)
{
    default_handler();
}

/**
 * @brief Pend SV handler
 */
void pend_sv_handler(void)
{
    default_handler();
}

/**
 * @brief System tick handler
 */
void sys_tick_handler(void)
{
    default_handler();
}
