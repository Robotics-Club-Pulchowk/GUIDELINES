/**
 ******************************************************************************
 * @file    crc8.hpp
 * @brief   Header file 8-bit crc calculation
 * @author  Robotics Team, IOE Pulchowk Campus
 ******************************************************************************
 */

#ifndef CRC8_HPP_
#define CRC8_HPP_

#include <cstdint>
#include <vector>

#ifndef CRC_POLYNOMIAL
#define CRC_POLYNOMIAL 7 /**< CRC Polynomial **/
#endif

// clang-format off
#define CRC_WIDTH               8           /**< CRC width */
#define CRC_HASH_TABLE_SIZE     256         /**< Size of CRC hash table */
#define TOP_BIT                 (1 << 7)    /**< Top bit position */
// clang-format on

/**
 * @brief Class for CRC-8 checksum calculation.
 */
class CRC8
{
public:
    /**
     * @brief Destructor for CRC8 class.
     */
    ~CRC8() {}

    /**
     * @brief Calculate CRC-8 checksum for uint8_t type data.
     * @param buf Pointer to the data buffer.
     * @param len Length of the data buffer.
     * @return CRC-8 checksum value.
     */
    uint8_t get_hash(uint8_t *buf, uint16_t len);

    /**
     * @brief Calculate CRC-8 checksum for std::vector<uint8_t> type data.
     * @param buf Reference of data buffer.
     * @param len Length of the data buffer.
     * @param start Index of starting position (default 0).
     * @return CRC-8 checksum value.
     */
    uint8_t get_hash(const std::vector<uint8_t> &buf, uint16_t len, uint16_t start = 0);

    static CRC8 Instance; /**< Singleton instance of CRC8 class. */

private:
    static uint8_t polynomial;                  /** CRC polynomial **/
    static uint8_t table_[CRC_HASH_TABLE_SIZE]; /**< CRC hash table. */

    /**
     * @brief Private constructor for CRC8 class.
     */
    CRC8();

    /**
     * @brief Initialize the CRC hash table.
     */
    static void initialize_table();
};

#endif // CRC_HPP_