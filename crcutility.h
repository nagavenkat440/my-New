#ifndef CRCUTILITY_H
#define CRCUTILITY_H

#include <QObject>

class CRCUtility
{
public:
    CRCUtility();
    static uint16_t g_update_crc(uint16_t crc, uint8_t newbyte);
    static uint16_t g_CRC_calc(const uint8_t *ptr, uint32_t pkt_size);

private:
    static const uint16_t POLY = 0x1021;
};

#endif // CRCUTILITY_H
