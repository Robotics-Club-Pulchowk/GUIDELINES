
#include <iostream>
#include <cstdint>
#include <cstring>
#include <math.h>
#include "crc8.hpp"
#include "serial.hpp"

struct Vector3f
{
    float x;
    float y;
    float z;
};

struct Vector4f
{
    float w;
    float x;
    float y;
    float z;
};

struct Euler
{
    float yaw;
    float pitch;
    float roll;
};

struct ImuMsg
{
    Vector4f orientation;
    Vector3f angular_velocity;
    Vector3f linear_acceleration;
};

void quaternion_to_ypr(const Vector4f &q, Euler &ypr)
{
    float sqw = q.w * q.w;
    float sqi = q.x * q.x;
    float sqj = q.y * q.y;
    float sqk = q.z * q.z;

    ypr.yaw = atan2(2.0 * (q.x * q.y + q.z * q.w), (sqi - sqj - sqk + sqw));
    ypr.pitch = asin(-2.0 * (q.x * q.z - q.y * q.w) / (sqi + sqj + sqk + sqw));
    ypr.roll = atan2(2.0 * (q.y * q.z + q.x * q.w), (-sqi - sqj + sqk + sqw));
}

void print_ypr(Euler ypr)
{
    printf("ypr: %f %f %f\n", ypr.yaw, ypr.pitch, ypr.roll);
}

void print(std::vector<uint8_t> v)
{
    for (uint8_t d : v)
    {
        std::cout << (int)d << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    Serial serial;
    ImuMsg imu_msg;
    Euler ypr;

    serial.Open("/dev/ttyUSB0");
    serial.SetBaudRate(LibSerial::BaudRate::BAUD_1152000);

    while (1)
    {
        serial.Receive((uint8_t*)&imu_msg, sizeof(imu_msg));
        quaternion_to_ypr(imu_msg.orientation, ypr);
        print_ypr(ypr);
    }

    serial.Close();
    return 0;
}
