# C++ Serial Communication

- [LibSerial](https://libserial.readthedocs.io/en/latest/index.html)


## Setup

Install `LibSerial` library.

```bash
sudo apt install libserial-dev
```

## Example: 1

We are going to receive IMU_*data from `MPU6050` into your `PC`.

1. Setup your MPU6050. Click [here](../markdown/MPU6050.md) for help.

2. Download `imu_serial_test.cpp`, `crc8.hpp` and  `crc8.cpp` from [here](../examples/cpp_serial_communication/example1/).

3. Compile the code.
   ```bash
   g++ imu_serial_test.cpp crc8.cpp -o imu_serial_test -lserial
   ```

4. Connect your `microcontroller with MPU6050`. The default serial address of the controller is `/dev/ttyUSB0` . If yours is different, you need to change in above code.

5. Run the program.
   ```bash
   ./imu_serial_test
   ```

## Example: 2

Example 1 is our old initial phase example which gives better idea of understanding. Now we have implemented abstraction on their
implementation. In this example, we are going to do same but in easy way with out updated library code. 

1. Setup your MPU6050. Click [here](../markdown/MPU6050.md) for help as example 1.

2. Dowload all codes from this [link](../examples/cpp_serial_communication/example2/).

3. Compile the code.
   ```bash
   g++ imu_serial_test.cpp crc8.cpp serial.cpp -o imu_serial_test -lserial
   ````

4. Connect your `microcontroller with MPU6050`. The default serial address of the controller is `/dev/ttyUSB0` . If yours is different, you need to change in above code.

5. Run the program.
   ```bash
   ./imu_serial_test
   ```

---
[Home](../BNOO8x.md)