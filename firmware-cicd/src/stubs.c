#include "button.h"
#include "system.h"
#include <stdint.h>

/* ── Button stubs ─────────────────────────────────────────────────────────── */

void button_init(void) { /* GPIO init would go here on real hardware */ }

uint8_t button_is_pressed(button_id_t btn)
{
    (void)btn;
    return 0; /* Always released in simulation */
}

/* ── System stubs ─────────────────────────────────────────────────────────── */

static uint32_t tick_counter = 0;

void system_init(void) { tick_counter = 0; }

uint32_t system_get_tick(void) { return tick_counter++; }
