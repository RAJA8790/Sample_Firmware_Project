#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

typedef enum {
    BUTTON_USER = 0
} button_id_t;

void    button_init(void);
uint8_t button_is_pressed(button_id_t btn);

#endif /* BUTTON_H */
