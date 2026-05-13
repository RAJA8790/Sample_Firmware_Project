#ifndef LED_H
#define LED_H

#include <stdint.h>

/* LED identifiers */
typedef enum {
    LED_GREEN = 0,
    LED_RED   = 1,
    LED_BLUE  = 2
} led_id_t;

/* LED states */
typedef enum {
    LED_OFF = 0,
    LED_ON  = 1
} led_state_t;

/* Function prototypes */
void        led_init(void);
void        led_set(led_id_t led, led_state_t state);
led_state_t led_get(led_id_t led);
void        led_toggle(led_id_t led);
void        led_all_off(void);

#endif /* LED_H */
