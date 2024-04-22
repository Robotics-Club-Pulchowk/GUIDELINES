#include <vector>
#include <cstring>
#include <iostream>

#include "crc8.hpp"
#include "serial.hpp"

SerialOpenStatus Serial::Open(const std::string &fileName,
                              const std::ios_base::openmode &openMode,
                              const bool &runOnFailure)
{
    try
    {
        SerialPort::Open(fileName, openMode);
    }
    catch (const LibSerial::AlreadyOpen &ex)
    {
        return SERIAL_ALREADY_OPEN;
    }
    catch (const LibSerial::OpenFailed &ex)
    {
        if (runOnFailure)
        {
            return SERIAL_OPEN_FAILED;
        }
        else
        {
            std::cerr << "Serial::Failed to open `" << fileName << "`" << std::endl;
            std::cerr << ex.what() << std::endl;
            throw;
        }
    }
    catch (const LibSerial::NotOpen &ex)
    {
        if (runOnFailure)
        {
            return SERIAL_NOT_OPEN;
        }
        else
        {
            std::cerr << "Serial::Not open `" << fileName << "`" << std::endl;
            std::cerr << ex.what() << std::endl;
            throw;
        }
    }

    return SERIAL_OK;
}

SerialReceiveStatus Serial::Receive(uint8_t *data, size_t dataSize, size_t timeOut)
{
    SerialReceiveStatus status = SERIAL_PACKET_NOT_RECEIVED;

    if (static_cast<size_t>(SerialPort::GetNumberOfBytesAvailable()) < dataSize + 1)
        return status;

    std::vector<uint8_t> inputBuffer(dataSize + 1);

    try
    {
        if (isWaitingForStart)
        {
            SerialPort::Read(inputBuffer, 1, timeOut);

            if (inputBuffer.front() == SERAL_START_BYTE)
            {
                isWaitingForStart = false;
                status = SERIAL_START_BYTE_MATCHED;
            }
            else
            {
                status = SERIAL_START_BYTE_DIDNT_MATCH;
            }
        }
        else
        {
            SerialPort::Read(inputBuffer, dataSize+1, timeOut);
            uint8_t hash = CRC8::Instance.get_hash(inputBuffer, dataSize);

            if (hash == inputBuffer.back())
            {
                std::memcpy(data, inputBuffer.data(), dataSize);
                status = SERIAL_DATA_RECEIVED;
            }
            else
            {
                return SERIAL_CRC_DIDNT_MATCH;
            }

            isWaitingForStart = true;
        }
    }
    catch (const LibSerial::ReadTimeout &ex)
    {
        status = SERIAL_READ_TIME_OUT;
    }

    return status;
}

void Serial::Transmit(uint8_t *data, size_t dataSize)
{
    std::vector<uint8_t> outputBuffer(dataSize + 2);

    outputBuffer.front() = SERAL_START_BYTE;
    std::memcpy(outputBuffer.data() + 1, data, dataSize);
    outputBuffer.back() = CRC8::Instance.get_hash(outputBuffer, dataSize, 1);

    SerialPort::Write(outputBuffer);
}