#include "crcutility.h"
#include "logger.h"

CRCUtility::CRCUtility()
{

}

uint16_t CRCUtility::g_update_crc(uint16_t crc, uint8_t newbyte) {
    crc ^= static_cast<uint16_t>(newbyte) << 8;
    for (uint8_t i = 0; i < 8; i++) {
        if (crc & 0x8000)
            crc = (crc << 1) ^ POLY;
        else
            crc <<= 1;
    }
    return crc;
}

uint16_t CRCUtility::g_CRC_calc(const uint8_t *ptr, uint32_t pkt_size) {
    uint16_t crc = 0xFFFF;
    for (uint32_t i = 0; i < pkt_size; i++) {
        crc = g_update_crc(crc, ptr[i]);
    }
    return crc;
}
