#include "dataprocessor.h"

DataProcessor::DataProcessor(QObject *parent)
    : QObject(parent)
{}

void DataProcessor::appendData(const QByteArray &data)
{
    QMutexLocker locker(&mutex);
    buffer.append(data);
}

void DataProcessor::clear_buffer()
{
    QMutexLocker locker(&mutex); // 🔒 Protect buffer access
    buffer.clear();              // Clear buffer more directly
    message.clear();
}
void DataProcessor::processData()
{
    QMutexLocker locker(&mutex);
    parseBuffer();
}

void DataProcessor::parseBuffer()
{
    int header = 0x24;
    QByteArray footer = QByteArray::fromHex("3B23");

    while (!buffer.isEmpty() && buffer.contains(header)) {
        int startIndex = buffer.indexOf(header);
        int endIndex = buffer.indexOf(footer, startIndex);

        if (endIndex != -1) {
            message = buffer.mid(startIndex, endIndex - startIndex + footer.size());
            emit dataProcessed(message);
            buffer.remove(0, endIndex + footer.size());
        } else {
            break; // wait for more data
        }
    }
}

//void DataProcessor::parseBuffer()
//{
//    /* ---------- protocol constants -------------------------------------------- */
//    static constexpr quint8 START_BYTE = 0x24;        // '$'
//    static constexpr quint16 FOOTER_WORD = 0x3B23;    // 0x23 0x3B on the wire
//    static constexpr int HDR_LEN = 1 + 1 + 2;         // start + MsgID + size
//    static constexpr int MIN_FRAME = HDR_LEN + 2 + 2; // +CRC +footer
//    static constexpr int MAX_FRAME = 512;             // upper sanity cap
//    const QByteArray FOOTER_SEQ = QByteArray::fromHex("3B23");

//    while (true) {
//        /* 1. Find the start byte ------------------------------------------------ */
//        int start = buffer.indexOf(static_cast<char>(START_BYTE));
//        if (start == -1) {
//            buffer.clear();
//            return;
//        }

//        /* 2. Do we have enough to read ID & size? ------------------------------- */
//        if (buffer.size() - start < HDR_LEN)
//            return; // incomplete header

//        quint8 msgId = static_cast<quint8>(buffer.at(start + 1));
//        quint8 sizeLo = static_cast<quint8>(buffer.at(start + 2));
//        quint8 sizeHi = static_cast<quint8>(buffer.at(start + 3));
//        quint16 packetSize = quint16(sizeLo) | (quint16(sizeHi) << 8);

//        /* 3. Decide whether the 16-bit size is believable ----------------------- */
//        int bytesAvail = buffer.size() - start;
//        bool size16_ok = packetSize >= MIN_FRAME && packetSize <= MAX_FRAME
//                         && packetSize <= bytesAvail;

//        /* If the 16-bit size looks crazy, fall back to the 8-bit sizeLo only.   */
//        if (!size16_ok)
//            packetSize = sizeLo;

//        /* 4. If even the reduced size is impossible, hunt for the footer ------- */
//        if (packetSize < MIN_FRAME || packetSize > bytesAvail) {
//            int endIdx = buffer.indexOf(FOOTER_SEQ, start + HDR_LEN);
//            if (endIdx == -1)
//                return; // footer not yet here
//            packetSize = endIdx - start + FOOTER_SEQ.size();
//        }

//        /* 5. Extract the candidate frame --------------------------------------- */
//        QByteArray frame = buffer.mid(start, packetSize);

//        /* 6. Verify footer ------------------------------------------------------ */
//        quint16 footer = static_cast<quint8>(frame.at(packetSize - 2))
//                         | (static_cast<quint16>(static_cast<quint8>(frame.at(packetSize - 1)))
//                            << 8);

//        if (footer != FOOTER_WORD) {
//            /* Bad footer → drop this '$' and resync --------------------------- */
//            buffer.remove(0, start + 1);
//            continue;
//        }

//        /* 7. (Optional) CRC check --------------------------------------------- */
//        // quint16 crcInFrame = ...;
//        // quint16 crcCalc    = myCrcCalc(frame.constData() + 1,
//        //                                packetSize - 1 - 2);
//        // if (crcInFrame != crcCalc) { buffer.remove(0, start + 1); continue; }

//        /* 8. Good frame – hand it over & erase it ------------------------------ */
//        emit dataProcessed(frame);
//        buffer.remove(0, start + packetSize);
//    }
//}

//void DataProcessor::parseBuffer()
//{
//    static constexpr char START_BYTE = 0x24;     // '$'
//    static constexpr quint16 END_WORD = 0x233B;  // footer in stream (little-endian)
//    static constexpr int MIN_HEADER = 1 + 1 + 2; // startByte + MsgID + packetSize

//    while (true) {
//        /* 1. Find the first possible frame start ---------------------------------------- */
//        int start = buffer.indexOf(START_BYTE);
//        if (start == -1) { // no start byte at all – flush junk and exit
//            buffer.clear();
//            return;
//        }

//        /* 2. Make sure we can at least read the packet-size field ------------------------ */
//        if (buffer.size() - start < MIN_HEADER)
//            return; // not enough bytes yet – wait for more data

//        /* 3. Read the 16-bit size field (little-endian) --------------------------------- */
//        quint16 packetSize = quint8(buffer.at(start + 2))
//                             | (quint16(quint8(buffer.at(start + 3))) << 8);

//        // Sanity-check the size (must cover at least header + footer)
//        if (packetSize < MIN_HEADER + 2 /*footer bytes*/) {
//            buffer.remove(0, start + 1); // corrupt frame – skip this byte and resync
//            continue;
//        }

//        /* 4. Wait until the whole frame is available ------------------------------------ */
//        if (buffer.size() - start < packetSize)
//            return; // frame incomplete – wait for more data

//        /* 5. Extract the complete frame ------------------------------------------------- */
//        QByteArray frame = buffer.mid(start, packetSize);

//        /* 6. Verify footer -------------------------------------------------------------- */
//        quint16 footer = quint8(frame.at(packetSize - 2))
//                         | (quint16(quint8(frame.at(packetSize - 1))) << 8);

//        if (footer != END_WORD) {
//            // Not a valid frame – drop this start byte and hunt for the next one
//            buffer.remove(0, start + 1);
//            continue;
//        }

//        /* 7. (Optional) CRC check goes here --------------------------------------------- */
//        // quint16 crcInFrame = ...
//        // quint16 crcCalc    = myCrcCalc(frame.constData()+1, packetSize-1-2); // example
//        // if (crcInFrame != crcCalc) { ... }

//        /* 8. Deliver the good frame and remove it from the buffer ----------------------- */
//        emit dataProcessed(frame);
//        buffer.remove(0, start + packetSize);
//    }
//}

//void DataProcessor::parseBuffer()
//{
//    /* ---------- protocol constants -------------------------------------------------- */
//    static constexpr quint8 START_BYTE = 0x24;        // '$'
//    static constexpr quint16 FOOTER_WORD = 0x3B23;    // 0x23 0x3B on the wire
//    static constexpr int PROLOGUE_LEN = 1 + 1 + 2;    // start + MsgID + packetSize
//    static constexpr int MIN_FRAME_LEN = PROLOGUE_LEN // smallest valid frame is
//                                         + 2          //   CRC
//                                         + 2;         //   footer
//    static constexpr int MAX_FRAME_LEN = 512;         // sanity cap

//    while (true) {
//        /* 1. Search for the next possible header byte ($) ---------------------------- */
//        int start = buffer.indexOf(static_cast<char>(START_BYTE));
//        if (start == -1) { // none at all ➜ flush junk & exit
//            buffer.clear();
//            return;
//        }

//        /* 2. Make sure we can at least read the size field --------------------------- */
//        if (buffer.size() - start < PROLOGUE_LEN)
//            return; // need more bytes

//        /* 3. Extract the 16-bit packetSize (little-endian) --------------------------- */
//        const quint8 lo = static_cast<quint8>(buffer.at(start + 2));
//        const quint8 hi = static_cast<quint8>(buffer.at(start + 3));
//        const quint16 packetSize = quint16(lo) | (quint16(hi) << 8);

//        /* 3a. Robustness checks ------------------------------------------------------ */
//        if (packetSize < MIN_FRAME_LEN || packetSize > MAX_FRAME_LEN) {
//            // Size is clearly nonsense ➜ drop this '$' and re-sync
//            buffer.remove(0, start + 1);
//            continue;
//        }

//        /* 4. Wait until we have the whole frame ------------------------------------- */
//        if (buffer.size() - start < packetSize)
//            return; // not yet complete

//        /* 5. Grab the candidate frame ---------------------------------------------- */
//        QByteArray frame = buffer.mid(start, packetSize);

//        /* 6. Verify footer ---------------------------------------------------------- */
//        quint16 footer = static_cast<quint8>(frame.at(packetSize - 2))
//                         | (static_cast<quint16>(static_cast<quint8>(frame.at(packetSize - 1)))
//                            << 8);

//        if (footer != FOOTER_WORD) {
//            // Wrong footer ➜ drop this '$' and hunt for the next one
//            buffer.remove(0, start + 1);
//            continue;
//        }

//        /* 7. (Optional) CRC check goes here ---------------------------------------- */
//        // quint16 crcInFrame = ... ;
//        // quint16 crcCalc    = myCrcCalc(frame.constData() + 1, packetSize - 1 - 2);
//        // if (crcInFrame != crcCalc) { buffer.remove(0, start + 1); continue; }

//        /* 8. Good frame! Emit and scrub from buffer --------------------------------- */
//        emit dataProcessed(frame);
//        buffer.remove(0, start + packetSize);
//    }
//}
