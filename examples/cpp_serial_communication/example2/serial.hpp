#ifndef ROBOTLIBPC_SERIAL_HPP_
#define ROBOTLIBPC_SERIAL_HPP_

#include <libserial/SerialPort.h>
#include <string>

#ifndef SERIAL_START_BYTE
#define SERAL_START_BYTE 0xA5
#endif

enum SerialOpenStatus
{
    SERIAL_OK,
    SERIAL_ALREADY_OPEN,
    SERIAL_OPEN_FAILED,
    SERIAL_NOT_OPEN,
};

enum SerialReceiveStatus
{
    SERIAL_PACKET_NOT_RECEIVED,
    SERIAL_START_BYTE_MATCHED,
    SERIAL_START_BYTE_DIDNT_MATCH,
    SERIAL_DATA_RECEIVED,
    SERIAL_CRC_DIDNT_MATCH,
    SERIAL_READ_TIME_OUT
};

class Serial : public LibSerial::SerialPort
{
public:
    Serial() : isWaitingForStart(true) {}

    SerialOpenStatus Open(const std::string &fileName,
                          const std::ios_base::openmode &openMode = std::ios_base::in | std::ios_base::out,
                          const bool &runOnFailure = false);

    SerialReceiveStatus Receive(uint8_t *data, size_t dataSize, size_t timeOut = 0);

    void Transmit(uint8_t *data, size_t dataSize);

private:
    bool isWaitingForStart;
};

#endif // ROBOTLIBPC_SERIAL_HPP_