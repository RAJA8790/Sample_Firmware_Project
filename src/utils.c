/**
 * @file utils.c
 * @brief Utility functions for firmware
 * @author Firmware Team
 * @version 1.0.0
 */

#include "utils.h"
#include <string.h>

/**
 * @brief Firmware version string
 */
static const char firmware_version[] = "firmware_sample v1.0.0";

/**
 * @brief CRC32 lookup table
 */
static const uint32_t crc32_table[256] = {
    0x00000000U, 0x77073096U, 0xEE0E612CU, 0x990951BAU, 0x076DC419U, 0x706AF48FU, 0xE963A535U, 0x9E6495A3U,
    0x0EDB8832U, 0x79DCB8A4U, 0xE0D5E91EU, 0x97D2D988U, 0x09B64C2BU, 0x7EB17CBDU, 0xE7B82D07U, 0x90BF1D91U,
    0x1DB71064U, 0x6AB020F2U, 0xF3B97148U, 0x84BE41DEU, 0x1ADAD47DU, 0x6DDDE4EBU, 0xF4D4B551U, 0x83D385C7U,
    0x136C9856U, 0x646BA8C0U, 0xFD62F97AU, 0x8A65C9ECU, 0x14015C4FU, 0x63066CD9U, 0xFA44E5D6U, 0x8D079D40U,
    0x3B6E20C8U, 0x4C69105EU, 0xD56041E4U, 0xA2677172U, 0x3C03E4D1U, 0x4B04D447U, 0xD20D85FDU, 0xA50AB56BU,
    0x35B5A8FAU, 0x42B2986CU, 0xDBBBC9D6U, 0xACBCF940U, 0x32D86CE3U, 0x45DF5C75U, 0xDCD60DCFU, 0xABD13D59U,
    0x26D930ACU, 0x51DE003AU, 0xC8D75180U, 0xBFD06116U, 0x21B4F4B5U, 0x56B3C423U, 0xCFBA9999U, 0xB8BDA50FU,
    0x2802B89EU, 0x5F058808U, 0xC60CD9B2U, 0xB10BE924U, 0x2F6F7C87U, 0x58684C11U, 0xC1611DABU, 0xB6662D3DU,
    0x76DC4190U, 0x01DB7106U, 0x98D220BCU, 0xEFD5102AU, 0x71B18589U, 0x06B6B51FU, 0x9FBFE4A5U, 0xE8B8D433U,
    0x7807C9A2U, 0x0F00F934U, 0x9609A88EU, 0xE10E9818U, 0x7F6A0DBBU, 0x086D3D2DU, 0x91646C97U, 0xE6635C01U,
    0x6B6B51F4U, 0x1C6C6162U, 0x856534D8U, 0xF262004EU, 0x6C0695EDU, 0x1B01A57BU, 0x8208F4C1U, 0xF50FC457U,
    0x65B0D9C6U, 0x12B7E950U, 0x8BBEB8EAU, 0xFCB9887CU, 0x62DD1DDFU, 0x15DA2D49U, 0x8CD37CF3U, 0xFBD44C65U,
    0x4DB26158U, 0x3AB551CEU, 0xA3BC0074U, 0xD4BB30E2U, 0x4ADFA541U, 0x3DD895D7U, 0xA4D1C46DU, 0xD3D6F4FBU,
    0x4369E96AU, 0x346ED9FCU, 0xAD678846U, 0xDA60B8D0U, 0x44042D73U, 0x33031DE5U, 0xAA0A4C5FU, 0xDD0D7CC9U,
    0x5005713CU, 0x270241AAU, 0xBE0B1010U, 0xC90C2086U, 0x5A6CCA25U, 0x2D0EF2B3U, 0xB4BFF409U, 0xC3BC9A9FU,
    0x5027C09EU, 0x274D3C08U, 0xBE915B2U, 0xC7D7A8A4U, 0x59B33D07U, 0x2EB40D81U, 0xB7BD5C3BU, 0xC0BA6CADU
};

/**
 * @brief Calculate CRC32 checksum of data buffer
 * @param data Pointer to data buffer
 * @param length Length of data in bytes
 * @return CRC32 checksum value
 */
uint32_t crc32_calculate(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFFU;
    size_t i = 0U;
    
    if (data == NULL)
    {
        return 0U;
    }
    
    for (i = 0U; i < length; i++)
    {
        uint32_t byte = (uint32_t)data[i];
        uint32_t table_index = (crc ^ byte) & 0xFFU;
        crc = (crc >> 8U) ^ crc32_table[table_index];
    }
    
    return crc ^ 0xFFFFFFFFU;
}

/**
 * @brief Safe memory copy with bounds checking
 * @param dest Destination buffer pointer
 * @param src Source buffer pointer
 * @param count Number of bytes to copy
 * @param dest_size Size of destination buffer
 * @return Status code (0 = success, -1 = failure)
 */
int32_t safe_memcpy(void *dest, const void *src, size_t count, size_t dest_size)
{
    if ((dest == NULL) || (src == NULL) || (count > dest_size))
    {
        return -1;
    }
    
    (void)memcpy(dest, src, count);
    return 0;
}

/**
 * @brief Get firmware version string
 * @return Pointer to version string
 */
const char* get_firmware_version(void)
{
    return firmware_version;
}
