# C++ Serial Communication

- [LibSerial](https://libserial.readthedocs.io/en/latest/index.html)


## Setup

Install `LibSerial` library.

```bash
sudo apt install libserial-dev
```

## Example

We are going to receive IMU_*data from `MPU6050` into your `PC`.

1. Setup your MPU6050. [Click here for help](./MPU6050).

2. Create a file `serial_test.cpp`.

3. Copy and paste the contents.

    ```cpp
    #include <libserial/SerialPort.h>
    #include <libserial/SerialPort.h>
    #include <iostream>
    #include <cstdint>
    #include <cstring>
    #include <math.h>
    #include "crc8.hpp"
    
    struct euler_t
    {
        float yaw;
        float pitch;
        float roll;
    };
    
    struct ImuMsg
    {
        float orientation[4];
        float angular_velocity[3];
        float linear_acceleration[3];
    };
    
    void quaternion_to_ypr(float qr, float qi, float qj, float qk, euler_t *ypr)
    {
        float sqw = qr * qr;
        float sqi = qi * qi;
        float sqj = qj * qj;
        float sqk = qk * qk;
    
        ypr->yaw = atan2(2.0 * (qi * qj + qk * qr), (sqi - sqj - sqk + sqw));
        ypr->pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqw));
        ypr->roll = atan2(2.0 * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqw));
    }
    
    void print_ypr(euler_t ypr)
    {
        printf("ypr: %f %f %f\n", ypr.yaw, ypr.pitch, ypr.roll);
    }
    
    void print(std::vector<uint8_t> v)
    {
        for(uint8_t d : v)
        {
            std::cout << (int)d << ' ';
        }
    
        std::cout << std::endl;
    }
    
    int main()
    {
        const int BUFFER_SIZE = 1 + sizeof(ImuMsg);
    
        LibSerial::SerialPort serial_port;
        LibSerial::DataBuffer input_buffer(BUFFER_SIZE);
        ImuMsg imu_msg;
        euler_t ypr;
        CRC8 crc8(7);
    
        serial_port.Open("/dev/ttyUSB0");
        bool is_waiting_for_start_byte = true;
    
        while (1)
        {
            if (serial_port.GetNumberOfBytesAvailable() < BUFFER_SIZE)
                continue;;
    
            if (is_waiting_for_start_byte)
            {
                serial_port.Read(input_buffer, 1);
    
                if (input_buffer.front() == 0xA5)
                {
                    is_waiting_for_start_byte = false;
                }
                else
                {
                    std::cout << "Start Byte Error" << std::endl;
                }
            }
            else
            {
                serial_port.Read(input_buffer, sizeof(ImuMsg) + 1);
                uint8_t hash = crc8.get_hash(input_buffer, sizeof(ImuMsg));
    
                if (input_buffer.back() == hash)
                {
                    std::memcpy((uint8_t *)&imu_msg, input_buffer.data(), sizeof(imu_msg));
                    quaternion_to_ypr(imu_msg.orientation[0], imu_msg.orientation[1], imu_msg.orientation[2], imu_msg.orientation[3], &ypr);
                    print_ypr(ypr);
                }
                else
                {
                    std::cout << "Hash Error" << std::endl;
                }
                is_waiting_for_start_byte = true;
            }
        }
    
        serial_port.Close();
        return 0;
    }
    ```

4. Download `crc8.hpp` and `crc8.cpp` from https://github.com/Robotics-Club-Pulchowk/robotlibpc/tree/main/cpp/crypto and place them aside `serial_test.cpp`

5. Compile the code.
   ```bash
   g++ serial_test.cpp crc8.cpp -o serial_test -lserial
   ```

6. Connect your `microcontroller with MPU6050`. The default serial address of the controller is `/dev/ttyUSB0` . If yours is different, you need to change in above code.

6. Run the program.
   ```bash
   ./serial_test
   ```

---
[Home](./BNOO8x.md)