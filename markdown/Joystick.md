# Joystick Controller

We generally use `XBOX` controller or `PS4` Controller. Both are comapaticble to each other. It is recommended to use `wireless bluetooth` communication rather than using `USB`. 

## PS4 with ESP32

1. **Setup Arduino IDE**
   - Install `esp32 board` from Arduino Board Manager by Espressif.
   - Downlaod and install `PS4 controller library`. [Click here](https://www.arduino.cc/reference/en/libraries/ps4controller/)
   - For `ESP32 Wroom`, select board `ESP32-DA-WROOM-MODULE` from `Tools > Board > esp32`.
   - Select port from `Tools > Port`.

2. **Setup PS4 Controller**
   - Find out bluetooth mac address of esp32. Copy and upload below code to esp32.
      ```cpp
      #include "esp_bt_main.h"
      #include "esp_bt_device.h"
      #include "BluetoothSerial.h"

      BluetoothSerial SerialBT;

      void printDeviceAddress() {

        const uint8_t* point = esp_bt_dev_get_address();
        for (int i = 0; i < 6; i++) {
          char str[3];
          sprintf(str, "%02X", (int)point[i]);
          Serial.print(str);
          if (i < 5){
            Serial.print(":");
          }
        }
      }
      void setup() {
        Serial.begin(115200);
         SerialBT.begin("ESP32 Bluetooth");
        printDeviceAddress();
      }

      void loop() {}
      ```
   - Open `Serial Monitor`, you can see Bluetooth MAC address at bottom line.
   - [Download SixaxisPairTool](https://sixaxispairtool.en.lo4d.com/download) and install. This is only for windows platform.
   - Open SixaxisPairTool and Plug the `PS4 controller` to your PC using `USB Cable`. Driver for the controller will be installed, if it is first time.
   - Write the `Bluetooth Mac Address` of the `ESP32` into `Master MAC Adrress Field` and click update.

3. **Upload Code**
   - [Downlaod esp32_ps4 codes](https://github.com/Robotics-Club-Pulchowk/Arduino_Codes/tree/main/esp32_ps4) and upload it to `ESP32`. You must define `DEBUG` to see data on `Serial Monitor`.
   - Press `PS4 Button` to power on and connect. If you have set the mac address correctly, it will connect to ESP32 indicated by `solid blue color`.
   - See data on Serial Monitor. The control data is transmitted through `UART2` pins of esp32.

## PS4 with Pico W
- Install Poco SDK
Run the `pico_setup.sh` cloning from https://github.com/raspberrypi/pico-setup.git.
   ```bash
   git clone https://github.com/raspberrypi/pico-setup.git
   cd pico-setup
   export SKIP_VSCODE=1 && bash pico_setup.sh
   ```
- Clone this repository: `https://github.com/Robotics-Club-Pulchowk/picow_ds4.git` and update submodule.
   ```bash
   git clone https://github.com/Robotics-Club-Pulchowk/picow_ds4.git
   cd picow_ds4
   git submodule update --init --recursive
   ```
- Find out `MAC Address` of `PS4 Controller`. In easy way, connect it to yout PC and see the MAC Address.
- Get into the source code folder, open `Src/bt_hid.c`, scroll down a little and replace `remote_addr_string` value by the MAC address of PS4.
- To print data on 'Serial Monitor' enable stdio usb by editing this line of `Src/CMakeLists.txt`.
   ```cmake
   pico_enable_stdio_usb(picow_ds4 1)
   ```
- From the project directory, make build folder, execute cmake and makefile.
  ```bash
   cd picow_ds4
   git submodule update --init --recursive
   mkdir build
   cd build
   cmake .. # you might use `-DPICO_BOARD=pico_w -DPICO_SDK_PATH=/your/path/to/pico-sdk` if environment is not set
   make -j <no. of parallel threads>
   ```

   The `.uf2` file will be `build/src/picow_ds4.uf2`

- Hold the `boot button` and connect the `Pico W` to `PC` using `USB`.
- Drag and drop the `picow_ds4.uf2` file from `build/src` to `Pico W Mass Storage`. You also can use similar command.
   ```bash
   # Just hit `tab` `tab` after `/media`.
   cp picow_ds4.uf2 /media/pi/PICOW
   ```
- Long press `share` and `PS4 button` simultaneous untill `fast blink of PS4 LED`. It will connect to `Pico W`. Pico W blinks its `green LED` if no controller is connected and `solid green` if it detects and connects to a controller.

*Pico W sends uart packet same as ESP32 througth its UART0 default Tx and Rx pin i.e. pin 0 and 1.*

---
[Home](../README.md)