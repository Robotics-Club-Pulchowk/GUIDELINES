# C++ Serial Communication

- [LibSerial](https://libserial.readthedocs.io/en/latest/index.html)


## Setup

Install `LibSerial` library.

```bash
sudo apt install libserial-dev
```

## Example

We are going to receive IMU_*data from `MPU6050` into your `PC`.

1. Setup your MPU6050. Click [here](../markdown/MPU6050.md) for help.

2. Create a file `imu_serial_test.cpp`.

3. Download `imu_serial_test.cpp`, `crc8.hpp` and  `crc8.cpp` from [here](../examples//cpp_serial_communication/).

4. Compile the code.
   ```bash
   g++ imu_serial_test.cpp crc8.cpp -o imu_serial_test -lserial
   ```

5. Connect your `microcontroller with MPU6050`. The default serial address of the controller is `/dev/ttyUSB0` . If yours is different, you need to change in above code.

6. Run the program.
   ```bash
   ./imu_serial_test
   ```

---
[Home](../BNOO8x.md)