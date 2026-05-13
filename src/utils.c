#include <stdint.h>

/**
 * @brief Simple memory utility functions
 */

void *memset(void *s, int c, uint32_t n) {
    unsigned char *p = (unsigned char *)s;
    while (n-- > 0U) {
        *p++ = (unsigned char)c;
    }
    return s;
}

void *memcpy(void *dest, const void *src, uint32_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    while (n-- > 0U) {
        *d++ = *s++;
    }
    return dest;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return (int)(*s1 - *s2);
        }
        s1++;
        s2++;
    }
    return (int)(*s1 - *s2);
}

uint32_t strlen(const char *s) {
    uint32_t len = 0U;
    while (*s != '\0') {
        len++;
        s++;
    }
    return len;
}
