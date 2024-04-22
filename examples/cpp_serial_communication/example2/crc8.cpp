/***********************************************************************************************
 * @file crc8.cpp
 * @brief Implementation file for the crc8 class
 * @author Robotics Team, IOE Pulchowk Campus
 * @date 2024
 *
 * For more information on CRC calculation in C, \
 * see \link https://barrgroup.com/embedded-systems/how-to/crc-calculation-c-code \endlink.
 **********************************************************************************************/

#include "crc8.hpp"
#include <vector>

CRC8 CRC8::Instance;
uint8_t CRC8::polynomial;
uint8_t CRC8::table_[CRC_HASH_TABLE_SIZE];

CRC8::CRC8()
{
    polynomial = CRC_POLYNOMIAL;
    initialize_table();
}

void CRC8::initialize_table()
{
    uint8_t remainder;
    int dividend = 0;

    for (; dividend < 256; ++dividend)
    {
#if CRC_WIDTH == 8
        remainder = dividend;
#else
        remainder = dividend << (CRC_WIDTH - 8);
#endif
        for (uint8_t b = 8; b > 0; --b)
        {
            if (remainder & TOP_BIT)
            {
                remainder = (remainder << 1) ^ polynomial;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
        table_[dividend] = remainder;
    }
}

uint8_t CRC8::get_hash(uint8_t *buf, uint16_t len)
{
    uint8_t data;
    uint8_t remainder = 0;

    for (uint16_t index = 0; index < len; ++index)
    {
#if CRC_WIDTH == 8
        data = buf[index] ^ remainder;
#else
        data = buf[index] ^ (remainder >> (CRC_WIDTH - 8));
#endif
        remainder = table_[data] ^ (remainder << 8);
    }

    return remainder;
}

uint8_t CRC8::get_hash(const std::vector<uint8_t> &buf, uint16_t len, uint16_t start)
{
    uint8_t data;
    uint8_t remainder = 0;

    for (uint16_t index = start; index < start + len; ++index)
    {
#if CRC_WIDTH == 8
        data = buf.at(index) ^ remainder;
#else
        data = buf.at(index) ^ (remainder >> (WIDTH - 8));
#endif
        remainder = table_[data] ^ (remainder << 8);
    }

    return remainder;
}