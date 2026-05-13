/**
 * @file utils.h
 * @brief Utility functions for firmware
 * @author Firmware Team
 * @version 1.0.0
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Calculate CRC32 checksum
 * @param data Pointer to data buffer
 * @param length Length of data in bytes
 * @return CRC32 checksum value
 */
uint32_t crc32_calculate(const uint8_t *data, size_t length);

/**
 * @brief Safe memory copy with bounds checking
 * @param dest Destination buffer pointer
 * @param src Source buffer pointer
 * @param count Number of bytes to copy
 * @param dest_size Size of destination buffer
 * @return Status code (0 = success, -1 = failure)
 */
int32_t safe_memcpy(void *dest, const void *src, size_t count, size_t dest_size);

/**
 * @brief Get firmware version string
 * @return Pointer to version string
 */
const char* get_firmware_version(void);

#endif /* UTILS_H */
